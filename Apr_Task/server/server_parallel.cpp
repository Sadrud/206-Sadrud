#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <stdexcept>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <omp.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../methods/methods.cpp"

constexpr int PORT = 8080;
constexpr int BACKLOG = 10;
constexpr size_t CHUNK_SIZE = 1024 * 64;
constexpr double epsilon = 1e-20;

std::mutex queue_mutex;
std::condition_variable queue_cv;
std::queue<int> client_queue;
bool server_running = true;

std::vector<int> convert_string_to_int(const std::string &str) {
	std::vector<int> numbers;
	std::stringstream ss(str);
	int num;
	while (ss >> num) numbers.push_back(num);
	return numbers;
}

std::string convert_int_to_string(const std::vector<int> &vec) {
	std::ostringstream oss;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (i != 0) oss << " ";
		oss << vec[i];
	}
	return oss.str();
}

std::vector<int> process_data(std::vector<int> &data) {
	if (data.empty()) throw std::runtime_error("Received empty data");

	double intpart = std::sqrt(data.size());
	if (std::abs(intpart - std::floor(intpart)) > epsilon)
		throw std::runtime_error("Data size is not a square: " + std::to_string(data.size()));

	std::vector<std::vector<int>> matrix((int)intpart, std::vector<int>((int)intpart));
	for (int i = 0; i < intpart; ++i)
		for (int j = 0; j < intpart; ++j)
			matrix[i][j] = data[i * (int)intpart + j];

	return FindEulerPath((int)intpart, matrix);
}

void send_all(int sock, const std::string &data) {
	ssize_t sent = send(sock, data.c_str(), data.length(), 0);
	if (sent <= 0) throw std::runtime_error("Send failed");
}

void handle_connection(int client_fd) {
	char buffer[CHUNK_SIZE];
	std::string received_data;

	while (true) {
		ssize_t bytes_received = recv(client_fd, buffer, CHUNK_SIZE - 1, 0);
		if (bytes_received <= 0) break;
		buffer[bytes_received] = '\0';
		received_data += std::string(buffer);
	}

	try {
		auto data = convert_string_to_int(received_data);
		auto result = process_data(data);
		auto response = convert_int_to_string(result);
		send_all(client_fd, response);
	} catch (const std::exception &e) {
		std::cerr << "Error in client handler: " << e.what() << std::endl;
	}

	close(client_fd);
}

void accept_connections(int server_fd) {
	while (server_running) {
		sockaddr_storage client_addr;
		socklen_t sin_size = sizeof(client_addr);
		int client_fd = accept(server_fd, (sockaddr *)&client_addr, &sin_size);
		if (client_fd == -1) continue;

		std::lock_guard<std::mutex> lock(queue_mutex);
		client_queue.push(client_fd);
		queue_cv.notify_one();
	}
}

int main() {
	addrinfo hints{}, *servinfo;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int rv = getaddrinfo(nullptr, std::to_string(PORT).c_str(), &hints, &servinfo);
	if (rv != 0) {
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		return 1;
	}

	int server_fd = -1;
	for (addrinfo *p = servinfo; p != nullptr; p = p->ai_next) {
		server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (server_fd == -1) continue;

		int yes = 1;
		setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(server_fd);
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);

	if (server_fd == -1 || listen(server_fd, BACKLOG) == -1) {
		std::cerr << "Server setup failed." << std::endl;
		return 1;
	}

	std::thread accept_thread(accept_connections, server_fd);

	omp_set_num_threads(4);
#pragma omp parallel
	{
		while (server_running) {
			int client_fd = -1;
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				queue_cv.wait(lock, [] { return !client_queue.empty(); });
				client_fd = client_queue.front();
				client_queue.pop();
			}

			if (client_fd == -1) continue;

			try {
				handle_connection(client_fd);
			} catch (const std::exception &e) {
				std::cerr << "Thread " << omp_get_thread_num() << " error: " << e.what() << std::endl;
			}
		}
	}

	accept_thread.join();
	close(server_fd);
	return 0;
}

