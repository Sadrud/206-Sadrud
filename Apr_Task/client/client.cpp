/*!
 * @file client.cpp
 * @brief TCP-клиент для передачи файлов
 * @author Sadrud
 * @date 2025
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <filesystem>
#include "../tests/tests.cpp"
#include <chrono>
#include <thread>

const int PORT = 8080;
const size_t CHUNK_SIZE = 65536;

namespace fs = std::filesystem;

/*!
 * @brief Обход всех файлов в папке
 * @param[in] folder_path Название папки
 * @return Возвращает вектор из файлов, находящихся в папке
 */
std::vector<fs::path> get_files_in_directory(const std::string& folder_path) {
	std::vector<fs::path> files;

	for (const auto& entry : fs::directory_iterator(folder_path)) {
		if (entry.is_regular_file()) files.push_back(entry.path());
	}

	return files;
}

/*!
 * @brief Конвертация строки в вектор из double
 * @param[in] str Строка, хранящая координаты точек
 * @return Возвращает вектор из чисел
 */
std::vector<int> convert_string_to_int (const std::string& str) {
	std::vector<int> numbers;
	std::stringstream ss(str);
	int num;

	while (ss >> num) numbers.push_back(num);

	return numbers;
}

/*!
 * @brief Запись вектора из чисел в файл специальным образом: 4 числа в строке
 * @param[in] filename, vec Название файла, куда записываем и вектор, откуда записываем
 */
void write_in_file (const std::string& filename, std::vector<int> vec) {
	std::ofstream outfile(filename);
	if (!outfile) throw std::runtime_error("Cannot create output file");

	for (int i = 0; i < vec.size(); i++)
		outfile << vec[i] << " "; }

/*!
 * @class Socket
 * @brief Сокет
 */
class Socket {
	public:
		/*!
		 * @brief Создание сокета
		 * @param[in] fd Дискриптор
		 */
		Socket(int fd) : fd_(fd) {}
		/*!
		 * @brief Удаление сокета и закрытие дискриптора
		 */
		~Socket() { if (fd_ != -1) close(fd_); }
		Socket(const Socket&) = delete; ///< Запрет вызова конструктора копирования
		Socket& operator=(const Socket&) = delete; ///< Запрет присваивания
		/*!
		 * @brief 'Отключение' второго сокета и присваивание второго изначальному
		 * @param[in] other Другой сокет
		 */
		Socket(Socket&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
		/*!
		 * @brief 'Отключение' второго сокета и присваивание второго изначальному
		 * @param[in] other Другой сокет
		 * @return Возвращает себя	
		 */
		Socket& operator=(Socket&& other) noexcept {
			if (this != &other) {
				fd_ = other.fd_;
				other.fd_ = -1;
			}
			return *this;
		}
		/*!
		 * @brief Получение значения дискриптора
		 * @return Возвращает дискриптор
		 */
		int get() const { return fd_; }
		void reset() { if (fd_ != -1) close(fd_); fd_ = -1; } ///< 'Отключение' сокета, если дискриптор равен -1

	private:
		int fd_ = -1;
};

/*!
 * @class FileClient
 * @brief TCP-клиент для взаимодействия с сервером
 */
class FileClient {
	public:
		/*!
		 * @brief Конструктор клиента для установки соединения с сервером
		 * 
		 * @details Выполняет следующие действия:
		 * 1. Получает информацию о сервере через getaddrinfo()
		 * 2. Перебирает все возможные адреса сервера
		 * 3. Создает сокет и пытается подключиться к серверу
		 * 4. Освобождает ресурсы после установки соединения
		 * 
		 * @param[in] hostname Имя хоста или IP-адрес сервера
		 * 
		 * @throw std::runtime_error в случаях:
		 * - Ошибки получения адресов сервера (getaddrinfo)
		 * - Неудачного подключения ко всем доступным адресам
		 */
		FileClient(const std::string& hostname) {
			addrinfo hints{}, *servinfo;
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;

			int rv;
			if ((rv = getaddrinfo(hostname.c_str(), std::to_string(PORT).c_str(), &hints, &servinfo)) != 0) {
				throw std::runtime_error(gai_strerror(rv));
			}

			for (addrinfo* p = servinfo; p != nullptr; p = p->ai_next) {
				sock_ = Socket(socket(p->ai_family, p->ai_socktype, p->ai_protocol));
				if (sock_.get() == -1) continue;

				if (connect(sock_.get(), p->ai_addr, p->ai_addrlen) == -1) {
					sock_.reset();
					continue;
				}
				break;
			}

			freeaddrinfo(servinfo);

			if (sock_.get() == -1) {
				throw std::runtime_error("Failed to connect");
			}
		}

		/*!
		 * @brief Отправляет содержимое файла на сервер
		 * 
		 * @details Выполняет следующие действия:
		 * 1. Открывает указанный файл для чтения
		 * 2. Читает файл построчно, объединяя строки через пробел
		 * 3. Отправляет все данные через сокет
		 * 4. Закрывает соединение на запись (SHUT_WR)
		 * 
		 * @param[in] file_path Путь к файлу для отправки
		 * 
		 * @throw std::runtime_error в случаях:
		 * - Невозможности открыть файл
		 * - Ошибки чтения файла (не достигнут конец файла)
		 * - Ошибки отправки данных (внутри send_all)
		 */
		void send_file(const std::string& file_path) {
			std::ifstream file(file_path, std::ios::in);
			if (!file) throw std::runtime_error("Cannot open input file");

			std::string buffer;

			for (std::string value; std::getline(file, value); ) { buffer += (value + ' '); }

			if (!file.eof()) throw std::runtime_error("Ошибка чтения файла");
			send_all(sock_.get(), buffer);
			std::cout << file_path << std::endl;

			shutdown(sock_.get(), SHUT_WR);
		}

		/*!
		 * @brief Принимает файл данных от сервера и сохраняет его на диск
		 * 
		 * @details Выполняет последовательно:
		 * 1. Прием данных от сервера чанками фиксированного размера (CHUNK_SIZE)
		 * 2. Конвертацию полученных строковых данных в вектор чисел
		 * 3. Сохранение результата в указанный файл
		 * 
		 * @param[in] save_path Путь для сохранения файла с полученными данными
		 */
		void receive_file(const std::string& save_path) {
			char buffer[CHUNK_SIZE];
			std::string data;
			std::vector<int> result;
			while (true) {
				ssize_t bytes_received = recv(sock_.get(), buffer, CHUNK_SIZE, 0);
				if (bytes_received <= 0) { break; }
				buffer[bytes_received] = 0;

				std::string val (buffer);
				data += val;
			}

			result = convert_string_to_int(data);
			write_in_file (save_path, result);
		}

	private:
		Socket sock_{-1};

		/*!
		 * @brief Отправка сообщения обратно (обертка над функцией send())
		 * @param[in] sock, vector Передаем дескриптор и строку, хранящую координаты точек вершин всех прямоугольников
		 */
		static void send_all(int sock, std::string vector){
			ssize_t sent = send(sock, vector.c_str(), vector.length(), 0);
			if (sent <= 0 || sent != vector.length()) throw std::runtime_error("Send failed");
		}

		/*!
		 * @brief Получает указатель на IP-адрес в структуре sockaddr
		 *
		 * @details Функция определяет тип адреса (IPv4/IPv6) и возвращает указатель
		 * на соответствующее поле с IP-адресом в унифицированном формате.
		 * @param[in] sa Указатель на структуру sockaddr (может быть sockaddr_in или sockaddr_in6)
		 * @return Указатель на IP-адрес в виде:
		 * - struct in_addr* для IPv4 (AF_INET)
		 * - struct in6_addr* для IPv6 (AF_INET6)
		 */
		static void* get_in_addr(sockaddr* sa) {
			if (sa->sa_family == AF_INET) {
				return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
			}
			return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
		}
};

/*!
 * @brief Функция, которая будет запускаться в отдельном потоке (для тестирования подключения многих клиентов)
 * @details Функция:
 * 1. Инициализирует переменные, создающие произвольные числа
 * 2. Создает тесты с помощью функций, из файла ../tests/tests.cpp
 * 3. Определяет файлы, в которых хранятся числа
 * 4. Создает несколько клиентов в цикле для обработки всех файлов из папки (каждая папка обрабатывается в отдельном потоке)
 * 5. Оповещает об записи полученных данных с сервера в файл
 *
 * @param[in] hostname, folder_path IP сервера и название папки, в которой хранятся файлы с числами
 */
void client_thread_func(const std::string& hostname, const std::string& input_path, const std::string& output_path) {
	try {
		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(1,10);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(2, 8);

		std::random_device rd3;
		std::mt19937 gen3(rd3());
		std::uniform_real_distribution<double> dist3(0.1,0.7);

		GraphTests::randomTest(input_path, dist1(gen1), dist2(gen1), dist3(gen1));
		GraphTests::randomTest(input_path, dist1(gen2), dist2(gen2), dist3(gen2));
		GraphTests::randomTest(input_path, dist1(gen3), dist2(gen3), dist3(gen3));
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}


	try {
#ifdef _WIN32
		mkdir(output_path.c_str());
#else
		mkdir(output_path.c_str(), 0777);
#endif
		auto files = get_files_in_directory(input_path);
		for (const auto& file : files) {
			FileClient client(hostname);
			client.send_file(input_path + '/' + static_cast<std::string>(file.filename()));
			client.receive_file(output_path + '/' + static_cast<std::string>(file.filename()));
		}
		std::cout << "File transfer completed successfully\n";
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

/*!
 * @brief Запуск сервера
 */
int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <hostname>, <quantity of clients>\n";
		return 1;
	}

	int num_clients = std::atoi(argv[2]);
	std::vector<std::thread> client_threads;

	std::string a = "input";
	std::string b = "output";
	for (int i = 0; i < num_clients; ++i) {
		client_threads.emplace_back(client_thread_func, argv[1], a + std::to_string(i+1), b + std::to_string(i+1));
	}
	for (auto& thread : client_threads) {
		thread.join();
	}

	return 0;
}
