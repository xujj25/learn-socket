#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main() {
	// input the filename to check whether creating file successfully
	char filename[100] = {0}; // filename
	printf("Input filename to save: ");
	fgets(filename, 100, stdin);

	// validate input filename
	if (strlen(filename) > 0) {
		filename[strlen(filename) - 1] = '\0';
	} else {
		puts("Filename input error");
		system("pause");
		exit(0);
	}

	FILE *fp = fopen(filename, "wb"); // open(create) file in binary mode
	if (fp == NULL) {
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}


	// creat socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// send request to specified server
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // use IPv4
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP addr
	serv_addr.sin_port = htons(1234); // port
	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// loop receiving data, until finish transfering the file
	char buffer[BUF_SIZE] = {0}; // file buffer
	int ncount;
	while ((ncount = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
		fwrite(buffer, ncount, 1, fp);
	}
	printf("File transfer success\n");

	// close socket directly
	// no need to use shutdown()
	fclose(fp);
	close(sock);

	return 0;
}