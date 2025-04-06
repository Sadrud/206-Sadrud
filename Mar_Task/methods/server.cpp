#include <iostream>
#include <fstream>
#include <vector>
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

const int PORT = 3490;
const int BACKLOG = 10;
const size_t CHUNK_SIZE = 65536;

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

class FileServer {
	public:
		FileServer() {
			setup_signal_handler();
			create_socket();
		}

		void run() {
			while (true) {
				sockaddr_storage their_addr{};
				socklen_t sin_size = sizeof their_addr;

				Socket client_socket(accept(sock_.get(), reinterpret_cast<sockaddr*>(&their_addr), &sin_size));
				if (client_socket.get() == -1) continue;

				char s[INET6_ADDRSTRLEN];
				inet_ntop(their_addr.ss_family,
						get_in_addr(reinterpret_cast<sockaddr*>(&their_addr)),
						s, sizeof s);

				std::cout << "Connection from " << s << std::endl;

				if (fork() == 0) {
					sock_.reset();
					handle_connection(std::move(client_socket));
					exit(0);
				}
			}
		}

	private:
		Socket sock_{-1};

		void setup_signal_handler() {
			struct sigaction sa{};
			sa.sa_handler = [](int) { while (waitpid(-1, nullptr, WNOHANG) > 0); };
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_RESTART;
			if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
				throw std::runtime_error("sigaction failed");
			}
		}

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

		static void* get_in_addr(sockaddr* sa) {
			if (sa->sa_family == AF_INET) {
				return &(reinterpret_cast<sockaddr_in*>(sa)->sin_addr);
			}
			return &(reinterpret_cast<sockaddr_in6*>(sa)->sin6_addr);
		}

		static void process_data(std::vector<char>& data) {
			std::transform(data.begin(), data.end(), data.begin(),
					[](unsigned char c) { return std::toupper(c); });
		}

		static void handle_connection(Socket&& client_socket) {
			std::vector<char> buffer(CHUNK_SIZE);
			std::vector<char> received_data;

			while (true) {
				ssize_t bytes_received = recv(client_socket.get(), buffer.data(), buffer.size(), 0);
				if (bytes_received <= 0) break;
				received_data.insert(received_data.end(), buffer.begin(), buffer.begin() + bytes_received);
				std::cout << "я тут" << std::endl;
			}

			std::cout << "я тут" << std::endl;
			if (!received_data.empty()) {
				process_data(received_data);
				send_all(client_socket.get(), received_data.data(), received_data.size());
			}
			std::cout << "я тут" << std::endl;
		}

		static void send_all(int sock, const char* data, size_t size) {
			size_t total_sent = 0;
			while (total_sent < size) {
				ssize_t sent = send(sock, data + total_sent, size - total_sent, 0);
				if (sent <= 0) throw std::runtime_error("Send failed");
				total_sent += sent;
			}
		}
};

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
