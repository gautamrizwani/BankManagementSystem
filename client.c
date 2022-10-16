#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<unistd.h>
#include<stdbool.h>
#include<strings.h>
#include<string.h>

#include "./Structs/Admin.h"
#include "./Structs/NormalAcc.h"
#include "./Structs/JointAcc.h"
#include "./Func/getPass.h"

void attemptNormalUserLogin(int sd);
void attemptJointUserLogin(int sd);
void attemptAdminLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
int option,currUserID;

void red() {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset() {
  printf("\033[0m");
}

void chooseOption(int sd){
	printf("1 : Normal-User Login\n");
	printf("2 : Joint Account-User Login\n");
	printf("3 : Admin Login\n");
	printf("Choose an option : ");
	red();
	scanf("%d",&option);
	yellow();
	printf("Option : %d\n",option);

	switch(option){
		case 1 :
			attemptNormalUserLogin(sd);
			break;
		case 2 :
			attemptJointUserLogin(sd);
			break;
		case 3 :
			attemptAdminLogin(sd);
			break;
		default :
			printf("Invalid option!\n\n");
			chooseOption(sd);
			break;
	}
	return;
}

void showMenu(int sd){
	int select;
	if(option==1 || option==2){
		printf("1 : Deposit        \n");
		printf("2 : Withdraw       \n");
		printf("3 : Balance Enquiry\n");
		printf("4 : Password Change\n");
		printf("5 : View Details   \n");
		printf("6 : Exit           \n");

		printf("Choose an option : ");
	red();
		scanf("%d",&select);
	yellow();
		printf("Option : %d\n",select);

		switch(select){
		case 1 :
			deposit(sd);
			break;
		case 2 :
			withdraw(sd);
			break;
		case 3 :
			balanceEnquiry(sd);
			break;
		case 4 :
			changePassword(sd);
			break;
		case 5 :
			viewDetails(sd);
			break;
		case 6 :
			write(sd,&select,sizeof(int));
			red();
			printf("Bye Bye!\n");
			yellow();
			exit(0);
		default :
			red();
			printf("Invalid option!\n\n");
			yellow();
			showMenu(sd);
			break;
		}
	}
	else if(option==3){
		printf("1 : Add Account    \n");
		printf("2 : Delete Account \n");
		printf("3 : Modify Account \n");
		printf("4 : Search Account \n");
		printf("5 : Exit           \n");

		printf("Choose an option : ");
	red();
		scanf("%d",&select);
	yellow();
		printf("Option : %d\n",select);

		switch(select){
		case 1 :
			addAccount(sd);
			break;
		case 2 :
			deleteAccount(sd);
			break;
		case 3 :
			modifyAccount(sd);
			break;
		case 4 :
			searchAccount(sd);
			break;
		case 5 :
			write(sd,&select,sizeof(int));
			red();
			printf("Bye Bye!\n");
			yellow();
			exit(0);
		default :
			red();
			printf("Invalid option!\n\n");
			yellow();
			showMenu(sd);
			break;
		}
	}
}

void attemptNormalUserLogin(int sd){
	bool result;
	struct normalUser currUser;
	printf("User ID : ");
	red();
	scanf("%d",&currUser.userID);
	yellow();
	currUserID=currUser.userID;
	printf("Password : ");
	char* pass = getpass("");
	strcpy(currUser.password, pass);

	getchar();
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(struct normalUser));

	read(sd,&result,sizeof(result));

	if(!result){
		red();
		printf("Invalid login!\nEither your Password didn't match OR your Account is Deleted\n");
		yellow();
		chooseOption(sd);
	}
	else{
		red();
		printf("Succesfully logged in!\n\n");
		yellow();
	}
	return;
}

void attemptJointUserLogin(int sd){
	bool result;
	struct jointUser currUser;
	printf("User ID : ");
	red();
	scanf("%d",&currUser.userID);
	yellow();
	currUserID=currUser.userID;  
	printf("Password : ");
	char* pass = getpass("");
	strcpy(currUser.password, pass);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(struct jointUser));

	read(sd,&result,sizeof(result));

	if(!result){
		red();
		printf("Invalid login!\nEither your Password didn't match OR your Account is Deleted\n");
		yellow();
		chooseOption(sd);
	}
	else{
		red();
		printf("Succesfully logged in!\n\n");
		yellow();
	}
	return;
}

void attemptAdminLogin(int sd){
	bool result;
	struct admin currUser;
	printf("User ID : ");
	red();
	scanf("%d",&currUser.userID);
	yellow();
	currUserID=currUser.userID;
	printf("Password : ");
	char* pass = getpass("");
	strcpy(currUser.password, pass);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(struct admin));

	read(sd,&result,sizeof(result));

	if(!result){
		red();
		printf("Invalid login!\nEither your Password didn't match OR your Account is Deleted\n");
		yellow();
		chooseOption(sd);
	}
	else{
		red();
		printf("Succesfully logged in!\n\n");
		yellow();
	}
	return;
}

void deposit(int sd){
	float amt;
	int select=1;
	bool result;

	printf("Amount to Deposit : Rs.");
	red();
	scanf("%f",&amt);
	yellow();

	while(amt<=0){
		printf("Enter a valid amount!\n");
		printf("Amount to Deposit : Rs.");
		red();
		scanf("%f",&amt);
		yellow();
	}

	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result));

	if(!result){
		red();
		printf("Error depositing your money!\n\n");
		yellow();
	}
	else{
		red();
		printf("Succesfully deposited!\n\n");
		yellow();
	}
	showMenu(sd);
	return;
}

void withdraw(int sd){
	float amt;
	int select=2;
	bool result;

	printf("Amount to Withdraw : Rs.");
	red();
	scanf("%f",&amt);
	yellow();

	while(amt<=0){
		printf("Enter a valid amount!\n");
		printf("Amount to Withdraw : Rs.");
		red();
		scanf("%f",&amt);
		yellow();
	}

	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result));

	if(!result){
		red();
		printf("Error withdrawing your money, Insufficient balance\n\n");
		yellow();
	}
	else{
		red();
		printf("Succesfully withdrew!\n\n");
		yellow();
	}
	showMenu(sd);
	return;
}

void balanceEnquiry(int sd){
	float amt;
	int select=3;
	int len;

	write(sd,&select,sizeof(int));

	len=read(sd,&amt,sizeof(float));	
	red();
	printf("Available Balance :: Rs.");
	printf("%0.2f\n\n",amt);
	yellow();
	showMenu(sd);
	return;
}

void changePassword(int sd){
	int select=4;
	char oPassword[10];
	char nPassword[10];
	bool result;

	printf("Enter your current password : ");
	char* pass = getpass("");
        strcpy(oPassword, pass);

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,oPassword,sizeof(oPassword));
	printf("Enter the new password(max 10 characters) : ");
	pass = getpass("");
        strcpy(nPassword, pass);
	write(sd,nPassword,sizeof(nPassword));

	read(sd,&result,sizeof(result));
	red();
	if(!result){
		printf("Error changing your password!\n\n");
	}
	else{
		printf("Succesfully changed your password!\n\n");
	}
	yellow();
	showMenu(sd);
	return;
}

void viewDetails(int sd){
	int select=5;

	//to the server
	write(sd,&select,sizeof(int));

	if(option==1){
		struct normalUser currUser1;
		read(sd,&currUser1,sizeof(struct normalUser));
		red();
		printf("User ID : %d\n",currUser1.userID);
		printf("Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
		printf("Status : %s\n\n",currUser1.status);
		yellow();
	}
	else if(option==2){
		struct jointUser currUser2;
		read(sd,&currUser2,sizeof(struct jointUser));
		red();
		printf("User ID : %d\n",currUser2.userID);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
		printf("Status : %s\n\n",currUser2.status);
		yellow();
	}
	showMenu(sd);
	return;
}

void addAccount(int sd){
	int select=1;
	int type;
	bool result;
	char rdBuff[1000];
	bzero(rdBuff, sizeof(rdBuff));

	write(sd,&select,sizeof(int));

	printf("Enter the type account\n1: Normal Account\n2: Joint Account\n");
	red();
	scanf("%d",&type);
	yellow();

	write(sd,&type,sizeof(int));

	if(type==1){
		struct normalUser addUser1;
		printf("Name of the account holder : ");
		red();
		scanf(" %[^\n]",addUser1.name);
		yellow();
		printf("Password(max 10 characters) : ");
		char* pass = getpass("");
        	strcpy(addUser1.password, pass);

		printf("Initial Deposit : Rs.");
		red();
		scanf("%f",&addUser1.balance);
		yellow();
		write(sd,&addUser1, sizeof(struct normalUser));
		read(sd, rdBuff, sizeof(rdBuff));
	}

	if(type==2){
		struct jointUser addUser2;
		printf("Name of the primary account holder : ");
		red();
		scanf(" %[^\n]",addUser2.name1);
		yellow();
		printf("Name of the other account holder : ");
		red();
		scanf(" %[^\n]",addUser2.name2);
		yellow();
		printf("Password(max 10 characters) : ");
		char* pass = getpass("");
                strcpy(addUser2.password, pass);

		printf("Initial Deposit : Rs.");
		red();
		scanf("%f",&addUser2.balance);
		yellow();
		write(sd,&addUser2,sizeof(struct jointUser));
		read(sd, rdBuff, sizeof(rdBuff));
	}

	read(sd,&result,sizeof(result));

	if(!result){
		printf("Error adding the account!\n\n");
	}
	else{
		printf("Succesfully added the account!\n\n");
	}
	red();
	printf("%s\n",rdBuff);
	yellow();
	showMenu(sd);
	return;
}

void deleteAccount(int sd){
	int select=2;
	int type,userID;
	bool result;

	write(sd,&select,sizeof(int));

	printf("Enter the type account\n1: Normal Account\n2: Joint Account\n");
	red();
	scanf("%d",&type);
	yellow();

	write(sd,&type,sizeof(int));

	printf("User ID : ");
	red();
	scanf("%d",&userID);
	yellow();
	write(sd,&userID,sizeof(int));

	read(sd,&result,sizeof(result));
	red();
	if(!result){
		printf("Error deleting the account ,please re-check the User ID!\n\n");
	}
	else{
		printf("Succesfully deleted the account!\n\n");
	}
	yellow();
	showMenu(sd);
	return;
}

void modifyAccount(int sd){
	int select=3;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	printf("Enter the type account\n1: Normal Account\n2: Joint Account\n");
	red();
	scanf("%d",&type);
	yellow();

	write(sd,&type,sizeof(int));

	if(type==1){
		struct normalUser modUser1;
		printf("Enter the User ID to be modified : ");
		red();
		scanf("%d",&modUser1.userID);
		yellow();
		printf("Enter Account Number to verify the User ID : ");
        	red();
                scanf("%d",&modUser1.account_no);
        	yellow();
		printf("New Name of the account holder : ");
		red();
		scanf(" %[^\n]",modUser1.name);
		yellow();
		printf("New Password(max 10 characters) : ");
		char* pass = getpass("");
                strcpy(modUser1.password, pass);

		write(sd,&modUser1,sizeof(struct normalUser));
	}

	if(type==2){
		struct jointUser modUser2;
		printf("Enter the User ID to be modified : ");
		red();
		scanf("%d",&modUser2.userID);
		yellow();
		printf("Enter Account Number to verify the User ID : ");
        	red();
                scanf("%d",&modUser2.account_no);
        	yellow();
		printf("New Name of the primary account holder : ");
		red();
		scanf(" %[^\n]",modUser2.name1);
		yellow();
		printf("New Name of the other account holder : ");
		red();
		scanf(" %[^\n]",modUser2.name2);
		yellow();
		printf("New Password(max 10 characters) : ");
		char* pass = getpass("");
                strcpy(modUser2.password, pass);
		write(sd,&modUser2,sizeof(struct jointUser));
	}

	read(sd,&result,sizeof(result));
	red();
	if(!result){
		printf("Error modifying the account ,please re-check the User ID and Account No!\n\n");
	}
	else{
		printf("Succesfully modified the account!\n\n");
	}
	yellow();
	showMenu(sd);
	return;
}

void searchAccount(int sd){
	int select=4;
	int type,len;
	bool result;

	write(sd,&select,sizeof(int));

	printf("Enter the type account\n1: Normal Account\n2: Joint Account\n");
	red();
	scanf("%d",&type);
	yellow();

	write(sd,&type,sizeof(int));

	if(type==1){
		struct normalUser searchUser1;
		int userID;
		printf("User ID : ");
		red();
		scanf("%d",&userID);
		yellow();
		write(sd,&userID,sizeof(int));

		len=read(sd,&searchUser1,sizeof(struct normalUser));
		if(len==0){
			printf("Please re-check the User ID!\n\n");
		}
		else{
			red();
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.status);
			yellow();
		}
	}

	if(type==2){
		struct jointUser searchUser2;
		int userID1;
		printf("User ID : ");
		red();
		scanf("%d",&userID1);
		yellow();
		write(sd,&userID1,sizeof(int));

		len=read(sd,&searchUser2,sizeof(struct jointUser));
		if(len==0){
			printf("Please re-check the User ID!\n\n");
		}
		else{
			red();
			printf("User ID : %d\n",searchUser2.userID);
			printf("Main Account Holder's Name : %s\n",searchUser2.name1);
			printf("Other Account Holder's Name : %s\n",searchUser2.name2);
			printf("Account Number : %d\n",searchUser2.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.status);
			yellow();
		}
	}
	showMenu(sd);
	return;
}

int main(){
	system("clear");
	yellow();
	printf("Welcome to ");
        red();
        printf("IIITBank\n\n");
	yellow();
	struct sockaddr_in server;    
	int sd,msgLength;
	char buff[50];
	char result;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5555);

	connect(sd,(struct sockaddr *)&server,sizeof(server));
	chooseOption(sd);
	showMenu(sd);
	close(sd);
	return 0;
}
