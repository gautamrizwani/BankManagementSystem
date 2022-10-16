#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>   // Internet Protocol family
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <errno.h>

#include"./Structs/Admin.h"
#include"./Structs/RegularAcc.h"
#include"./Structs/JointAcc.h"

struct normalUser getNormalUser(int ID){
	int i=ID;
	struct normalUser currUser;
	int fd=open("NUfile",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    	     //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

struct jointUser getJointUser(int ID){
	int i=ID;
	struct jointUser currUser;
	int fd=open("JUfile",O_RDONLY,0744);

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

struct admin getAdmin(int ID){
	int i=ID;
	struct admin currUser;
	int fd=open("ADfile",O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct admin);    	     //nth record
	lock.l_len=sizeof(struct admin);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return currUser;
}

bool checkNormalUser(struct normalUser currUser){
	int i=currUser.userID;
	int fd=open("NUfile",O_RDONLY,0744);
	bool result;
	struct normalUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    	     //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct normalUser));
	printf("%d\n%s\n%s\n",temp.userID, temp.name, temp.password);
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkJointUser(struct jointUser currUser){
	int i=currUser.userID;
	int fd=open("JUfile",O_RDONLY,0744);
	bool result;
	struct jointUser temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct jointUser));
	printf("%d\n%s\n%s\n%s\n",temp.userID, temp.name1, temp.name2, temp.password);
	if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))
		result=true;
	else
		result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAdmin(struct admin currUser){
	int i=currUser.userID;
	int fd=open("ADfile",O_RDONLY,0744);
	bool result;
	struct admin temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct admin);    	     //nth record
	lock.l_len=sizeof(struct admin);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(i)*sizeof(struct admin),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&temp,sizeof(struct admin));
	printf("%d\n%s\n%s\n",temp.userID, temp.username, temp.password);
	if(!strcmp(temp.password,currUser.password))	result=true;
	else						result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool depositMoney(int accType,int ID,float amt){
	int i=ID;
	printf("hiii\n");
	if(accType==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amt;
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else	result=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(!strcmp(currUser.status,"ACTIVE")){
			currUser.balance+=amt;
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;
		// printf("hiii\n");
		sleep(10);
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool withdrawMoney(int accType,int ID,float amt){
	int i=ID;
	if(accType==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(!strcmp(currUser.status,"ACTIVE") && currUser.balance>=amt){
			currUser.balance-=amt;
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float getBalance(int accType,int ID){
	int i=ID;
	float result;
	if(accType==1){
		int i=ID;
		int fd=open("NUfile",O_RDONLY,0744);
		struct normalUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    	     //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(struct normalUser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int i=ID;
		int fd=open("JUfile",O_RDONLY,0744);
		struct jointUser temp;

		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    	     //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&temp,sizeof(struct jointUser));
		if(!strcmp(temp.status,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool alterPassword(int accType,int ID,char newPwd[10]){
	int i=ID;
	if(accType==1){
		int fd=open("NUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct normalUser);    //nth record
		lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct normalUser currUser;
		lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct normalUser));

		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(struct normalUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open("JUfile",O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(struct jointUser);    //nth record
		lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
		lock.l_pid=getpid();

		fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
		//getchar();

		struct jointUser currUser;
		lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
		read(fd,&currUser,sizeof(struct jointUser));

		if(!strcmp(currUser.status,"ACTIVE")){
			strcpy(currUser.password,newPwd);
			lseek(fd,sizeof(struct jointUser)*(-1),SEEK_CUR);
			write(fd,&currUser,sizeof(struct jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool addNormalUser(struct normalUser record, int sd){
	int fd=open("NUfile",O_RDWR,0744);
	struct normalUser endUser;
	int flag=0;
        if (fd == -1 && errno == ENOENT)
        {
		fd=open("NUfile",O_RDWR | O_CREAT | O_APPEND,0744);
                record.userID = 0;
		record.account_no=10000;
		flag=1;
        }
	bool result;
	
	int fl1;
	char wrBuff[1000];
	bzero(wrBuff, sizeof(wrBuff));
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(struct normalUser);    //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	lseek(fd,(-1)*sizeof(struct normalUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(struct normalUser));

	if(flag==0)
	{
		record.userID=endUser.userID+1;
		record.account_no=endUser.account_no+1;
	}
	printf("User ID = %d\n", record.userID);
	sprintf(wrBuff, "%s%d\n","User ID of your new Account is ",record.userID);
	strcpy(record.status,"ACTIVE");

	int j=write(fd,&record,sizeof(struct normalUser));
	if(j!=0)	result=true;
	else	result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	write(sd, wrBuff, sizeof(wrBuff));
	return result;
}

bool addJointUser(struct jointUser record){
	int fd=open("JUfile",O_RDWR,0744);
	int flag=0;
        if (fd == -1 && errno == ENOENT)
        {
                fd=open("JUfile",O_RDWR | O_CREAT | O_APPEND,0744);
                record.userID = 0;
                record.account_no=10000;
                flag=1;
        }
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(struct jointUser);    //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	struct jointUser endUser;
	lseek(fd,(-1)*sizeof(struct jointUser),SEEK_END);  //changing the file pointer to the selected record
	read(fd,&endUser,sizeof(struct jointUser));

	if(flag==0)
	{
		record.userID=endUser.userID+1;
		record.account_no=endUser.account_no+1;
	}
	strcpy(record.status,"ACTIVE");

	int j=write(fd,&record,sizeof(struct jointUser));
	if(j!=0)	result=true;
	else	result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteNormalUser(int ID){
	int i=ID;
	int fd=open("NUfile",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	struct normalUser currUser;
	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	if(!strcmp(currUser.status,"ACTIVE")){
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;

		lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(struct normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deleteJointUser(int ID){
	int i=ID;
	int fd=open("JUfile",O_RDWR,0744);
	bool result;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	struct jointUser currUser;
	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	if(!strcmp(currUser.status,"ACTIVE")){
		strcpy(currUser.status,"CLOSED");
		currUser.balance=0;

		lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
		int j=write(fd,&currUser,sizeof(struct jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyNormalUser(struct normalUser modUser){
	int i=modUser.userID;
	int fd=open("NUfile",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct normalUser);    //nth record
	lock.l_len=sizeof(struct normalUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	struct normalUser currUser;
	lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct normalUser));

	if(!strcmp(currUser.status,"ACTIVE") && (modUser.account_no==currUser.account_no)){
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(struct normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool modifyJointUser(struct jointUser modUser){
	int i=modUser.userID;
	int fd=open("JUfile",O_RDWR,0744);
	bool result=false;

	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct jointUser);    //nth record
	lock.l_len=sizeof(struct jointUser);	             //sizeof(record)
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	struct jointUser currUser;
	lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);  //changing the file pointer to the selected record
	read(fd,&currUser,sizeof(struct jointUser));

	if(!strcmp(currUser.status,"ACTIVE")  && (modUser.account_no==currUser.account_no)){
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
		int j=write(fd,&modUser,sizeof(struct jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

void serverTask(int nsd){
	int msgLength,select,type,option,accType,currUserID;
	bool result;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			struct normalUser currUser1;
			accType=1;
			msgLength=read(nsd,&currUser1,sizeof(struct normalUser));
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			currUserID=currUser1.userID;
			result=checkNormalUser(currUser1);
			write(nsd,&result,sizeof(result));
		}
		else if(option==2){
			struct jointUser currUser2;
			accType=2;
			msgLength=read(nsd,&currUser2,sizeof(struct jointUser));
			currUserID=currUser2.userID;
			printf("Username : %d\n",currUser2.userID);
			printf("Password : %s\n",currUser2.password);
			result=checkJointUser(currUser2);
			write(nsd,&result,sizeof(result));
		}
		else if(option==3){
			struct admin currUser3;
			accType=3;
			msgLength=read(nsd,&currUser3,sizeof(struct admin));
			currUserID=currUser3.userID;
			printf("Username : %d\n",currUser3.userID);
			printf("Password : %s\n",currUser3.password);
			result=checkAdmin(currUser3);
			write(nsd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;
	}

	while(1){
		read(nsd,&select,sizeof(int));
		if(option==1 || option==2){
			if(select==1){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=depositMoney(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=withdrawMoney(accType,currUserID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3){
				float amt;
				amt=getBalance(accType,currUserID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4){
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				result=alterPassword(accType,currUserID,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5){
				if(option==1){
					struct normalUser user1=getNormalUser(currUserID);
					write(nsd,&user1,sizeof(struct normalUser));
				}
				else if(option==2){
					struct jointUser user2=getJointUser(currUserID);
					write(nsd,&user2,sizeof(struct jointUser));
				}
			}
			else if(select==6)	break;
		}
		else if(option==3){
			read(nsd,&type,sizeof(int));
			if(select==1){
				if(type==1){
					struct normalUser newUser1;
					read(nsd,&newUser1,sizeof(struct normalUser));
					result=addNormalUser(newUser1, nsd);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					struct jointUser newUser2;
					read(nsd,&newUser2,sizeof(struct jointUser));
					result=addJointUser(newUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2){
				if(type==1){
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					result=deleteNormalUser(delUserID1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					result=deleteJointUser(delUserID2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3){
				if(type==1){
					struct normalUser modUser1;
					read(nsd,&modUser1,sizeof(struct normalUser));
					result=modifyNormalUser(modUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					struct jointUser modUser2;
					read(nsd,&modUser2,sizeof(struct jointUser));
					result=modifyJointUser(modUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4){
				if(type==1){
					struct normalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=getNormalUser(userID1);
					write(nsd,&searchUser1,sizeof(struct normalUser));
				}
				else if(type==2){
					struct jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=getJointUser(userID2);
					write(nsd,&searchUser2,sizeof(struct jointUser));
				}
			}
			else if(select==5)	break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

int main(){
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;    
	server.sin_addr.s_addr=INADDR_ANY; 
	server.sin_port=htons(5555);
	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);	     
	write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));
	while(1){
		clientLen = sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
		if(!fork()){
			close(sd);
			serverTask(nsd);
			exit(0);
		}
		else{
			close(nsd);
		}
	}
	return 0;
}
