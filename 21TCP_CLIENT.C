#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 70 /* MAX NUMBER OF BYTES WE CAN GET ONCE*/
#define PORT 5000 /* PORT CLIENT WILL BE CONNECTED TO*/
#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("INPUT STRING : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("OK\n");
			break;
		}
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// SOCKET CREATION AND VERIFICATION
	sockfd = socket(AF_INET, SOCK_RAW, 0);
	if (sockfd == -1) {
		printf("SOCKET FAILED\n");
		exit(0);
	}
	else
		printf("SOCKET CREATED \n");
	bzero(&servaddr, sizeof(servaddr));

	// ASSIGN IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("13.53.76.30");
	servaddr.sin_port = htons(PORT);

	// CONNECTING CLIENT TO SERVER
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("ERROR\n");
		exit(0);
	}
	else
		printf("CONNECTED\n");

	// close the socket
	close(sockfd);
}

