
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 2000

int main () {

	printf("Hello, world!\n");

	char buffer[BUFFER_SIZE];

	char boilerplatehttp[] = ""
				  "HTTP/1.0 200 OK\r\n"
                  "Server: miwebserver!\r\n"
                  "Content-type: text/plain\r\n"
				  "<html>\r\n"
				  "john cena tacos!"
				  "</html>\r\n";


	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sockfd == -1 ) {
		perror("webserver (socket)");	
		return -1;
	}

	printf("socket created successfully!\n");


	struct sockaddr_in host_addr;
	int host_addrlen = sizeof(host_addr);

	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) == -1 ){
		perror("webserver bind");
		return 1;
	}

	printf("successfully bound to address \n");

	if ( listen ( sockfd, SOMAXCONN ) == -1 ) {
		perror("webserver. listen.");
		return 1;
	}
	printf("listening for connections...\n");

	while(1){

		int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);

		if (newsockfd < 0){
			perror("webserver accept");
			continue;
		}

		printf("connection accepted! \n");


		int readfd = read(newsockfd, buffer, BUFFER_SIZE);
		if (readfd == -1){
			perror("webserver. read");
			continue;
		}

		printf(";BEGIN content\n");
		for ( int i = 0; i < readfd; i++){
			putchar(buffer[i]);

		}
		printf(";END content\n");

		snprintf(buffer, BUFFER_SIZE, "yeeeet!");
//		strncat(buffer, boilerplatehttp, 1000);


		//int response = write(newsockfd, buffer, BUFFER_SIZE);
		int response = write(newsockfd, boilerplatehttp, strlen(boilerplatehttp));

		if (response == -1 ){
			perror("webserver. response");
			continue;
		}

		close(newsockfd);

	}


//	return 0;
}
