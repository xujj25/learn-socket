#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

int main() {
	// send request to specified server
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // use IPv4
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP addr
	serv_addr.sin_port = htons(1234); // port

	char buf_send[BUF_SIZE] = {0};
	char buf_recv[BUF_SIZE] = {0};
	
	while (1) {
		// creat socket
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		// get character user input and send to server
		printf("Input a string: ");
		fgets(buf_send, BUF_SIZE, stdin);
		send(sock, buf_send, strlen(buf_send), MSG_NOSIGNAL);

		// read data from server
		recv(sock, buf_recv, BUF_SIZE, 0);
		printf("Message from server: %s\n", buf_recv);
		
		memset(buf_send, 0, BUF_SIZE); // reset send buffer
		memset(buf_recv, 0, BUF_SIZE); // reset recv buffer
		// close socket
		close(sock);
	}

	return 0;
}