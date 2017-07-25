#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

int main()
{
	// check if the file exists
	char *filepath = "/home/xujijun/testfile/music.mp3";
	FILE *fp = fopen(filepath, "rb"); // Open the file in binary mode
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	// create socket
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// set addr reusable
	int reuse = 1;
	if (setsockopt(serv_sock, SOL_SOCKET, 
				SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
		printf("set addr reusable error!\n");
	}

	// bind socket with IP and port
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// listen for client's request
	listen(serv_sock, 100);

	// accept client request
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

	// loop sending data until the end of the file
	char buffer[BUF_SIZE] = {0}; // buffer
	int ncount;
	while ((ncount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		send(clnt_sock, buffer, ncount, 0);
	}

	// finish reading file, 
	// disconnect the output stream, 
	// send FIN package to client
	shutdown(clnt_sock, SHUT_WR);
	// block until the client finish receiving
	recv(clnt_sock, buffer, BUF_SIZE, 0);

	// close file
	fclose(fp);

	// close socket
	close(clnt_sock);
	close(serv_sock);

	return 0;
}