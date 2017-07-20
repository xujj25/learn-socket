#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
	// creat socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// send request to specified server
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // use IPv4
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP addr
	serv_addr.sin_port = htons(1234); // port
	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// read data from server
	char buffer[40];
	read(sock, buffer, sizeof(buffer) - 1);
	printf("Message from server: %s\n", buffer);
	

	memset(buffer, 0x00, sizeof(buffer));
	read(sock, buffer, sizeof(buffer) - 1);
	printf("Message from server: %s\n", buffer);

	// close socket
	close(sock);

	return 0;
}