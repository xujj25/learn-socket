#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100
int main () {
	// create socket
	int sock = socket(PF_INET, SOCK_DGRAM, 0);

	// server addr information
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family =PF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("138.68.10.209");
	serv_addr.sin_port = htons(1234);

	// loop fetching user's input and send to server
	// then receive data from server(echo)
	struct sockaddr from_addr;
	int addrLen = sizeof(from_addr);
	while (1) {
		char buffer[BUF_SIZE] = {0};
		printf("Input a string: ");
		fgets(buffer, BUF_SIZE, stdin);
		sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &from_addr, &addrLen);
		buffer[strLen] = 0;
		printf("Message from server: %s\n", buffer);
	}

	close(sock);

	return 0;
}