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
#include "../tests/clientTests.cpp"
#include <chrono>
#include <thread>

const int PORT = 8080;
const size_t CHUNK_SIZE = 65536;

namespace fs = std::filesystem;

std::vector<fs::path> get_files_in_directory(const std::string& folder_path) {
	std::vector<fs::path> files;

	for (const auto& entry : fs::directory_iterator(folder_path)) {
		if (entry.is_regular_file()) files.push_back(entry.path());
	}

	return files;
}

std::vector<double> convert_string_to_double (const std::string& str) {
	std::vector<double> numbers;
	std::stringstream ss(str);
	double num;

	while (ss >> num) numbers.push_back(num);

	return numbers;
}

void write_in_file (const std::string& filename, std::vector<double> vec) {
	std::ofstream outfile(filename, std::ios::app);
	if (!outfile) throw std::runtime_error("Cannot create output file");

	for (int i = 0; i < vec.size(); i++) {
		outfile << vec[i];
		if ((i + 1) % 4 == 0) {
			outfile << '\n'; 
		} else if (i != vec.size() - 1) {
			outfile << ' ';
		}
	}
}

class Socket {
	public:
		Socket(int fd) : fd_(fd) {}
		~Socket() { if (fd_ != -1) close(fd_); }
		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;
		Socket(Socket&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
		Socket& operator=(Socket&& other) noexcept {
			if (this != &other) {
				fd_ = other.fd_;
				other.fd_ = -1;
			}
			return *this;
		}
		int get() const { return fd_; }
		void reset() { if (fd_ != -1) close(fd_); fd_ = -1; }

	private:
		int fd_ = -1;
};

class FileClient {
	public:
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

		void send_file(const std::string& file_path) {
			std::ifstream file(file_path, std::ios::in);
			if (!file) throw std::runtime_error("Cannot open input file");

			std::string buffer;

			for (std::string value; std::getline(file, value); ) { buffer += (value + ' '); }

			if (!file.eof()) throw std::runtime_error("Ошибка чтения файла");
			send_all(sock_.get(), buffer);

			shutdown(sock_.get(), SHUT_WR);
		}

		void receive_file(const std::string& save_path) {
			char buffer[CHUNK_SIZE];
			std::string data;
			std::vector<double> result;
			while (true) {
				ssize_t bytes_received = recv(sock_.get(), buffer, CHUNK_SIZE, 0);
				if (bytes_received <= 0) { break; }
				buffer[bytes_received] = 0;

				std::string val (buffer);
				data += val;
			}

			result = convert_string_to_double(data);
			std::cout << "z nen" << std::endl;
			write_in_file (save_path, result);

		}

	private:
		Socket sock_{-1};

		static void send_all(int sock, std::string vector){
			ssize_t sent = send(sock, vector.c_str(), vector.length(), 0);
			if (sent <= 0) throw std::runtime_error("Send failed");
		}

		static void* get_in_addr(sockaddr* sa) {
			if (sa->sa_family == AF_INET) {
				return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
			}
			return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
		}
};

void client_thread_func(const std::string& hostname, const std::string& folder_path) {
	try {
		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<> dist1(1000,5000);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<> dist2(100, 1000);

		std::random_device rd3;
		std::mt19937 gen3(rd3());
		std::uniform_int_distribution<> dist3(10,100);


		ClientTests::randomTest1(folder_path, dist1(gen1), dist2(gen1), dist3(gen1));
		ClientTests::randomTest2(folder_path, dist1(gen2), dist2(gen2), dist3(gen2));
		ClientTests::randomTest3(folder_path, dist1(gen3), dist2(gen3), dist3(gen3));
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	try {
		auto files = get_files_in_directory(folder_path);
		for (const auto& file : files) {
			FileClient client(hostname);
			client.send_file(folder_path + '/' + static_cast<std::string>(file.filename()));
			client.receive_file(folder_path + '/' + static_cast<std::string>(file.filename()));

		}
		std::cout << "File transfer completed successfully\n";
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <hostname>, <quantity of clients>\n";
		return 1;
	}

	int num_clients = std::atoi(argv[2]);
	std::vector<std::thread> client_threads;

	std::string a = "./input";
	for (int i = 0; i < num_clients; ++i) {
		client_threads.emplace_back(client_thread_func, argv[1], a + std::to_string(i+1));
	}
	for (auto& thread : client_threads) {
		thread.join();
	}

	return 0;
}
