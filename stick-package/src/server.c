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
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// bind socket with IP and port
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// listen for client's request
	listen(serv_sock, 20);

	// accept client request
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	char buffer[BUF_SIZE] = {0};
	int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

	sleep(10); // pause the program for 10s

	// receive data from client and return the same data
	int recv_len = recv(clnt_sock, buffer, BUF_SIZE, 0);
	send(clnt_sock, buffer, recv_len, 0);

	// close socket
	close(clnt_sock);
	close(serv_sock);

	return 0;
}