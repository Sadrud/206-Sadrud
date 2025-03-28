#include "erprog.h"


int main () {
	/* Сервер */
	int server = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr = {0, 0, 0, 0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons (34543);
	Bind (server, (struct sockaddr *) &adr, sizeof adr);
	Listen(server, 5);
	socklen_t adr_len = sizeof adr;
	int fd = Accept(server, (struct sockaddr *) &adr, &adr_len);

	ssize_t nread;
	char filename[256];
	nread = read (fd, filename, sizeof(filename)-1);
	filename[nread] = '\0';
	if (nread == -1) {
		perror ("read failure\n");
		exit (EXIT_FAILURE);
	}
	if (nread == 0) {
		printf ("END OF FILE occured\n");
	}
	write (STDOUT_FILENO, filename, nread);
	write (fd, filename, nread);
	
	sleep(15);
	
	close (fd);
	close (server);
	
	return 0;
}
