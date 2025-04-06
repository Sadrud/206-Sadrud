#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdint>

const int PORT = 3490;
const size_t CHUNK_SIZE = 65536;

uint64_t htonll(uint64_t value) {
	static const int num = 42;
	if (*reinterpret_cast<const char*>(&num) == num) {
		return ((uint64_t)htonl(value & 0xFFFFFFFF) << 32) | htonl(value >> 32);
	} else {
		return value;
	}
}

uint64_t ntohll(uint64_t value) {
	return htonll(value);
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
			std::ifstream file(file_path, std::ios::binary | std::ios::ate);
			if (!file) throw std::runtime_error("Cannot open input file");

			auto file_size = file.tellg();
			file.seekg(0);

			//int64_t net_size = htonll(file_size);
			//send_all(sock_.get(), reinterpret_cast<char*>(&net_size), sizeof(net_size));

			std::vector<char> buffer(CHUNK_SIZE);
			while (file.read(buffer.data(), buffer.size())) {
				size_t bytes_read = file.gcount();
				send_all(sock_.get(), buffer.data(), bytes_read);
			}

			if (file.gcount() > 0) {
				send_all(sock_.get(), buffer.data(), file.gcount());
			}
			shutdown(sock_.get(), SHUT_WR);
		}

		void receive_file(const std::string& save_path) {
			std::ofstream file(save_path, std::ios::binary);
			if (!file) throw std::runtime_error("Cannot create output file");

			std::vector<char> buffer(CHUNK_SIZE);
			while (true) {
				ssize_t bytes_received = recv(sock_.get(), buffer.data(), buffer.size(), 0);
				std::cout << "z nen" << std::endl;
				if (bytes_received <= 0) break;
				file.write(buffer.data(), bytes_received);
			}
			std::cout << "z nen" << std::endl;
		}

	private:
		Socket sock_{-1};

		static void send_all(int sock, const char* data, size_t size) {
			size_t total_sent = 0;
			while (total_sent < size) {
				ssize_t sent = send(sock, data + total_sent, size - total_sent, 0);
				if (sent <= 0) throw std::runtime_error("Send failed");
				total_sent += sent;
			}
		}

		static void* get_in_addr(sockaddr* sa) {
			if (sa->sa_family == AF_INET) {
				return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
			}
			return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
		}
};

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <hostname> <input_file> <output_file>\n";
		return 1;
	}

	try {
		FileClient client(argv[1]);
		client.send_file(argv[2]);
		client.receive_file(argv[3]);
		std::cout << "File transfer completed successfully\n";
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
