#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 3490;
const size_t BUFFER_SIZE = 4096;

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

class Client {
	public:
		Client(const std::string& hostname) {
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
				throw std::runtime_error("client: failed to connect");
			}
		}

		void send_data(const std::string& data) {
			send(sock_.get(), data.data(), data.size(), 0);

			std::vector<char> buffer(BUFFER_SIZE);
			ssize_t bytes_received = recv(sock_.get(), buffer.data(), buffer.size(), 0);
			if (bytes_received > 0) {
				std::cout.write(buffer.data(), bytes_received);
				std::cout << std::endl;
			}
		}

	private:
		Socket sock_{-1};

		static void* get_in_addr(sockaddr* sa) {
			if (sa->sa_family == AF_INET) {
				return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
			}
			return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
		}
};

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "usage: client hostname\n";
		return 1;
	}

	try {
		Client client(argv[1]);
		std::string input;
		std::cout << "Enter message to send: " << std::endl;
		std::cin >> input;
		client.send_data(input);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
