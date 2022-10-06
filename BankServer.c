#include <stdio.h>
#include <errno.h> 

#include <fcntl.h>  
#include <unistd.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>

#include "Macros.h"
#include "Admin.h"
#include "Cust.h"

void connHandler(int connFD);

void main() {
	int socFD, connFD;
	struct sockaddr_in Ser, Cli;

	socFD = socket(AF_INET, SOCK_STREAM, 0);

	Ser.sin_family = AF_INET;
	Ser.sin_port = htons(8080);
	Ser.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(socFD, (struct sockaddr *)&Ser, sizeof(Ser));
	
	listen(socFD, 5);

	while(1) {
		int cliSize = (int)sizeof(Cli);
		
		connFD = accept(socFD, (struct sockaddr *)&Cli, &cliSize);

		printf("IP of client: %s\n", inet_ntoa(Cli.sin_addr));

		if(!fork()) {
			connHandler(connFD);
			close(connFD);
			exit(0);
		}
		else
			close(connFD);
	}
	close(socFD);
}

void connHandler(int connFD) {
	printf("Inside Handler Function\n");

	char rdBuff[1000], wrBuff[1000];

	bzero(rdBuff, sizeof(rdBuff));
	bzero(wrBuff, sizeof(wrBuff));

	int choice;

	int status;

	status = write(connFD, INIT_MESS, sizeof(INIT_MESS));
	if (status == -1)
                    perror("Error while writing to network via socket!");
                else
                    printf("Data sent to client!\n");

	read(connFD, rdBuff, sizeof(rdBuff));
	
	choice = atoi(rdBuff);
	
	switch(choice) {
		case 1:
			adminHandler(connFD);
			break;
		case 2:
			custHandler(connFD);
			break;
		default:
			break;
	}
}
