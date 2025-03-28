#include "erprog.h"

int main() {
	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr = {0, 0, 0, 0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons(34543);
	Inet_pton(AF_INET, "127.0.0.0", &adr.sin_addr);
	Connect(fd, (struct sockaddr *) &adr, sizeof adr);
	write(fd, "Hello\n", 6);
	char buf[256];
	ssize_t nread;
	nread = read(fd, buf, 256);
	if (nread == -1) {
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if (nread == 0) {
		printf("EOF occured\n");
	}
	write(STDOUT_FILENO, buf, nread);
	sleep(10);
	close(fd);
	return 0;
}
