#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100

int main()
{
	// create socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	// bind socket
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = PF_INET; // use IPv4 address
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // get IP addr automatically
	serv_addr.sin_port = htons(1234); // port
	bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// receive client's request
	struct sockaddr clnt_addr; // client addr information
	int nsize = sizeof(clnt_addr);
	char buffer[BUF_SIZE];
	while (1) {
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &clnt_addr, &nsize);
		sendto(sock, buffer, strLen, 0, &clnt_addr, nsize);
	}

	close(sock);

	return 0;
}