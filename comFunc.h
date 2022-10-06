#ifndef COM_FUNC
#define COM_FUNC

#include <stdio.h>   
#include <unistd.h> 
#include <string.h> 
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdlib.h>
#include <errno.h>

#include "./Structs/Customer.h"

bool logHandler(bool isAdmin, int connFD, struct Cust *custDet);

bool logHandler(bool isAdmin, int connFD, struct Cust *custDet) {
	char rdBuff[1000], wrBuff[1000], tempBuff[1000];
	struct Cust custVar;
	int id;

	bzero(rdBuff, sizeof(rdBuff));
	bzero(wrBuff, sizeof(wrBuff));
	bzero(tempBuff, sizeof(tempBuff));

	if(isAdmin)
		strcpy(wrBuff, WELCOME_ADMIN);
	else
		strcpy(wrBuff, WELCOME_CUST);

	strcat(wrBuff, "\n");
	strcat(wrBuff, GET_UNAME);

	write(connFD, wrBuff, sizeof(wrBuff));

	read(connFD, rdBuff, sizeof(rdBuff));

	bool usrFound=false;

}

#endif
