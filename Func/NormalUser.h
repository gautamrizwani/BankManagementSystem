#ifndef NORMAL_USER
#define NORMAL_USER

struct normalUser getNormalUser(int ID){
        int i=ID;
        struct normalUser currUser;
        int fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDONLY,0744);

        int fl1;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct normalUser);   
        lock.l_len=sizeof(struct normalUser);    
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock); 

        lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);
        read(fd,&currUser,sizeof(struct normalUser));

        lock.l_type=F_UNLCK;
	printf("Press Enter to relese Lock from View Details\n");
	getchar();
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return currUser;
}

bool checkNormalUser(struct normalUser currUser){
        int i=currUser.userID;
        int fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDONLY,0744);
        bool result;
        struct normalUser temp;

        int fl1;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct normalUser);  
        lock.l_len=sizeof(struct normalUser);         
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);

        lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);
        read(fd,&temp,sizeof(struct normalUser));
        if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))   result=true;
        else                                            result=false;

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}

bool addNormalUser(struct normalUser record, int sd){
        int fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDWR,0744);
        struct normalUser endUser;
        int flag=0;
        if (fd == -1 && errno == ENOENT)
        {       
                fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDWR | O_CREAT | O_APPEND,0744);
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
        lock.l_start=(-1)*sizeof(struct normalUser); 
        lock.l_len=sizeof(struct normalUser);         
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock); 

        lseek(fd,(-1)*sizeof(struct normalUser),SEEK_END);
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
        if(j!=0)        result=true;
        else    result=false;

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        write(sd, wrBuff, sizeof(wrBuff));
        return result;
}

bool deleteNormalUser(int ID){
        int i=ID;
        int fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDWR,0744);
        bool result;

        int fl1;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct normalUser);
        lock.l_len=sizeof(struct normalUser);     
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);  

        struct normalUser currUser;
        lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET);
        read(fd,&currUser,sizeof(struct normalUser));

        if(!strcmp(currUser.status,"ACTIVE")){
                strcpy(currUser.status,"CLOSED");
                currUser.balance=0;

                lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
                int j=write(fd,&currUser,sizeof(struct normalUser));
                if(j!=0)        result=true;
                else            result=false;
        }

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}

bool modifyNormalUser(struct normalUser modUser){
        int i=modUser.userID;
        int fd=open("/home/ubuntu/MT2022142/Data/NormalUser.data",O_RDWR,0744);
        bool result=false;

        int fl1;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct normalUser); 
        lock.l_len=sizeof(struct normalUser);      
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);

        struct normalUser currUser;
        lseek(fd,(i)*sizeof(struct normalUser),SEEK_SET); 
        read(fd,&currUser,sizeof(struct normalUser));

	modUser.balance = currUser.balance;
        if(!strcmp(currUser.status,"ACTIVE") && (modUser.account_no==currUser.account_no)){
                strcpy(modUser.status,"ACTIVE");
                lseek(fd,(-1)*sizeof(struct normalUser),SEEK_CUR);
                int j=write(fd,&modUser,sizeof(struct normalUser));
                if(j!=0)        result=true;
                else            result=false;
        }

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}



#endif
