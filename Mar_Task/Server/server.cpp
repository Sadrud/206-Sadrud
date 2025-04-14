/**
 * @brief Основной модуль TCP-сервера для обработки геометрических данных
 */

#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sstream>
#include "../methods/Methods.hpp"


const int PORT = 8080;
const int BACKLOG = 10;
const size_t CHUNK_SIZE = 1024*64;

/**
 * @brief Конвертация строки в вектор из double
 * @param[in] str Строка, хранящая координаты точек
 */
std::vector<double> convert_string_to_double (const std::string& str) {
	std::vector<double> numbers;
	std::stringstream ss(str);
	double num;

	while (ss >> num) numbers.push_back(num);
	return numbers;
}

/**
 * @brief Конвертация чисел в string
 * @param[in] vec Набор чисел
 */
std::string convert_double_to_string (const std::vector<double>& vec) {
	std::ostringstream oss;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (i != 0) oss << " ";
		oss << vec[i];
	}
	std::string result = oss.str();
	return result;
}

/**
 * @class Socket
 * @brief Сокет
 */
class Socket {
	public:
		/**
		 * @brief Создание сокета
		 * @param[in] fd Дискриптор
		 */
		Socket(int fd) : fd_(fd) {}
		/**
		 * @brief Удаление сокета и закрытие дискриптора
		 */
		~Socket() { if (fd_ != -1) close(fd_); } 
		Socket(const Socket&) = delete; ///< Запрет вызова конструктора копирования
		/**
		 * @brief Запрет присваивания
		 * @return Ничего
		 */
		Socket& operator=(const Socket&) = delete;
		/**
		 * @brief 'Отключение' второго сокета и присваивание второго изначальному
		 * @param[in] other Другой сокет
		 */
		Socket(Socket&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
		/**
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
		/**
		 * @brief Получение значения дискриптора
		 * @return Возвращает дискриптор
		 */
		int get() const { return fd_; }
		void reset() { if (fd_ != -1) close(fd_); fd_ = -1; } ///< 'Отключение' сокета, если дискриптор равен -1

	private:
		int fd_ = -1;///< Дескриптор
};

/**
 * @class FileServer
 * @brief TCP-сервер для обработки прямоугольников
 */

class FileServer {
	public:
		FileServer() { ///< Конструктор сервера
			setup_signal_handler();
			create_socket();
		}

		/**
		 *@brief Основной цикл работы сервера
		 * 
		 * @details Выполняет следующие действия в бесконечном цикле:
		 * 1. Принимает входящие соединения через accept()
		 * 2. Определяет IP-адрес клиента
		 * 3. Создает дочерний процесс для обработки соединения
		 * 4. В дочернем процессе вызывает обработчик соединения
		 * @throw std::exception Может пробросить исключения из:
		 * - inet_ntop()
		 * - handle_connection()
		 * - Системные ошибки
		 */
		void run() {
			try{
				while (true) {
					sockaddr_storage their_addr{};
					socklen_t sin_size = sizeof their_addr;

					Socket client_socket(accept(sock_.get(), reinterpret_cast<sockaddr*>(&their_addr), &sin_size));
					if (client_socket.get() == -1) continue;

					char s[INET6_ADDRSTRLEN];
					inet_ntop(their_addr.ss_family,	get_in_addr(reinterpret_cast<sockaddr*>(&their_addr)), s, sizeof s);

					std::cout << "Connection from " << s << std::endl;

					if (fork() == 0) {
						sock_.reset();
						handle_connection(std::move(client_socket));
						exit(0);
					}
				}
			} catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}

	private:
		Socket sock_{-1};///< Создание сокета

		/**
		 * @brief Настраивает обработчик сигнала SIGCHLD для автоматического завершения дочерних процессов.
		 * 
		 * @details Функция выполняет следующие действия:
		 * Создает обработчик сигнала, который вызывает `waitpid()` для всех завершенных дочерних процессов.
		 * Использует флаг `SA_RESTART` для автоматического перезапуска системных вызовов, прерванных сигналом.
		 * Устанавливает пустую маску сигналов для обработчика.
		 * Регистрирует обработчик для сигнала SIGCHLD.
		 */
		void setup_signal_handler() {
			struct sigaction sa{};
			sa.sa_handler = [](int) { while (waitpid(-1, nullptr, WNOHANG) > 0); };
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_RESTART;
			if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
				throw std::runtime_error("sigaction failed");
			}
		}

		/**
		 * @brief Создает и настраивает серверный сокет для принятия подключений
		 * 
		 * @details Выполняет последовательно:
		 * 1. Получение информации о доступных адресах через getaddrinfo()
		 * 2. Создание сокета для каждого возможного адреса
		 * 3. Установка опции SO_REUSEADDR для быстрого переиспользования порта
		 * 4. Привязка сокета к адресу (bind)
		 * 5. Перевод сокета в режим прослушивания (listen)

		 @throw std::runtime_error в случаях:
		 - Ошибки получения адресов (getaddrinfo)
		 * - Неудачной привязки сокета (bind)
		 * - Ошибки перевода в режим прослушивания (listen)
		 */
		void create_socket() {
			addrinfo hints{}, *servinfo;
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_flags = AI_PASSIVE;

			int rv;
			if ((rv = getaddrinfo(nullptr, std::to_string(PORT).c_str(), &hints, &servinfo)) != 0) {
				throw std::runtime_error(gai_strerror(rv));
			}

			for (addrinfo* p = servinfo; p != nullptr; p = p->ai_next) {
				sock_ = Socket(socket(p->ai_family, p->ai_socktype, p->ai_protocol));
				if (sock_.get() == -1) {
					perror("socket creation failed");
					continue;
				}

				int yes = 1;
				if (setsockopt(sock_.get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
					perror("setsockopt failed");
					exit(1);
				}

				if (bind(sock_.get(), p->ai_addr, p->ai_addrlen) == -1) {
					perror("bind failed");
					sock_.reset();
					continue;
				}
				break;
			}

			freeaddrinfo(servinfo);

			if (sock_.get() == -1) {
				throw std::runtime_error("failed to bind socket");
			}

			if (listen(sock_.get(), BACKLOG) == -1) {
				throw std::runtime_error("listen failed");
			}

			std::cout << "Server listening on port " << PORT << std::endl;
		}

		/**
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

		/**
		 * @brief Производит вычисления и находит контур объединения прямоугольников, переданных от клиента
		 * @details Выполняется следующее:
		 * 1. Передается вектор значений
		 * 2. Вектор обрабатывается и определяются вершины прямоугольника
		 * 3. Создается и заполняется массив прямоугольников
		 * 4. Выполняется основноц алгоритм нахождения контура объединения прямоугольников
		 * 5. Контур записывается в список в виде ребер
		 * 6. Возвращается изменный вектор
		 *
		 * @param[in] data Вектор из чисел, которые являются координатами точек вершин прямоугольника.
		 */
		static void process_data(std::vector<double>& data) {
			if (data.size() % 8 != 0) throw std::runtime_error("Number of elements (" + std::to_string(data.size()) + ") is not divisible by 8");
			int quantity = data.size()/8;
			Rectangle* parr = new Rectangle[quantity];
			try {
				for (int i = 0; i < quantity; i++) { parr[i] = Rectangle(Point(data[8*i],data[8*i+1]), Point(data[8*i+4], data[8*i+5])); }
				List<Edge*>* edges = findContour (parr, quantity);
				data.clear();
				edges->save_vector(data);
				delete [] parr;
				delete edges;
			} catch (Exception& e) {
				e.print_message();
			}
		}

		/**
		 * @brief Обрабатывает соединение с клиентом
		 * 
		 * @details Функция выполняет:
		 * 1. Прием данных от клиента чанками фиксированного размера
		 * 2. Конвертацию полученных строковых данных в числовой формат
		 * 3. Обработку данных через process_data()
		 * 4. Отправку результата обратно клиенту
		 * 
		 * @param[in] client_socket Сокет клиента (передается по rvalue-ссылке)
		 */
		static void handle_connection(Socket&& client_socket) {
			std::string received_data_string;
			std::vector<double> received_data_double;
			std::string received_data;
			char buffer[CHUNK_SIZE];

			while (true) {
				ssize_t bytes_received = recv(client_socket.get(), buffer, CHUNK_SIZE, 0);
				if (bytes_received <= 0) break;
				buffer[bytes_received] = 0;
				std::string val(buffer);
				received_data_string += val;
			}

			received_data_double = convert_string_to_double(received_data_string);
			if (!received_data_double.empty()) {
				process_data(received_data_double);
				received_data = convert_double_to_string(received_data_double);
				send_all(client_socket.get(), received_data);
			}
		}

		/**
		 * @brief Отправка сообщения обратно (обертка над функцией send())
		 * @param[in] sock, data Передаем дескриптор и строку, хранящую координаты точек вершин всех прямоугольников
		 */
		static void send_all(int sock, std::string data) {
			ssize_t sent = send(sock, data.c_str(), data.length(), 0);
			if (sent <= 0) throw std::runtime_error("Send failed");
		}

};

/**
 * @brief Запуск сервера
 */
int main() {
	try {
		FileServer server;
		server.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
