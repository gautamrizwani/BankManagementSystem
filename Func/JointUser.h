#ifndef JOINT_USER
#define JOINT_USER

struct jointUser getJointUser(int ID){
        int i=ID;
        struct jointUser currUser;
        int fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDONLY,0744);

        int fl1;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct jointUser);          
        lock.l_len=sizeof(struct jointUser);               
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);

        lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);
        read(fd,&currUser,sizeof(struct jointUser));

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return currUser;
}

bool checkJointUser(struct jointUser currUser){
        int i=currUser.userID;
        int fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDONLY,0744);
        bool result;
        struct jointUser temp;

        int fl1;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct jointUser);     
        lock.l_len=sizeof(struct jointUser);          
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);  

        lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);
        read(fd,&temp,sizeof(struct jointUser));
        if(!strcmp(temp.password,currUser.password) && !strcmp(temp.status,"ACTIVE"))
                result=true;
        else
                result=false;

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}

bool addJointUser(struct jointUser record, int socfd){
        int fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDWR,0744);
        int flag=0;
        if (fd == -1 && errno == ENOENT)
        {
                fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDWR | O_CREAT | O_APPEND,0744);
                record.userID = 0;
                record.account_no=10000;
                flag=1;
        }
        bool result;

        int fl1;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence=SEEK_END;
        lock.l_start=(-1)*sizeof(struct jointUser);
        lock.l_len=sizeof(struct jointUser);      
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);

        struct jointUser endUser;
        lseek(fd,(-1)*sizeof(struct jointUser),SEEK_END);
        read(fd,&endUser,sizeof(struct jointUser));

        if(flag==0)
        {
                record.userID=endUser.userID+1;
                record.account_no=endUser.account_no+1;
        }
        strcpy(record.status,"ACTIVE");

	char wrBuff[1000];
	bzero(wrBuff, sizeof(wrBuff));
	printf("User ID = %d\n", record.userID);
        sprintf(wrBuff, "%s%d\n","User ID of your new Account is ",record.userID);

        int j=write(fd,&record,sizeof(struct jointUser));
        if(j!=0)        result=true;
        else    result=false;

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);

	write(socfd, wrBuff, sizeof(wrBuff));

        return result;
}

bool deleteJointUser(int ID){
        int i=ID;
        int fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDWR,0744);
        bool result;

        int fl1;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct jointUser);  
        lock.l_len=sizeof(struct jointUser);       
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock); 

        struct jointUser currUser;
        lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);
        read(fd,&currUser,sizeof(struct jointUser));

        if(!strcmp(currUser.status,"ACTIVE")){
                strcpy(currUser.status,"CLOSED");
                currUser.balance=0;

                lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
                int j=write(fd,&currUser,sizeof(struct jointUser));
                if(j!=0)        result=true;
                else            result=false;
        }

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}

bool modifyJointUser(struct jointUser modUser){
        int i=modUser.userID;
        int fd=open("/home/ubuntu/MT2022142/Data/JointUser.data",O_RDWR,0744);
        bool result=false;

        int fl1;
        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=(i)*sizeof(struct jointUser);   
        lock.l_len=sizeof(struct jointUser);        
        lock.l_pid=getpid();

        fl1=fcntl(fd,F_SETLKW,&lock);  

        struct jointUser currUser;
        lseek(fd,(i)*sizeof(struct jointUser),SEEK_SET);
        read(fd,&currUser,sizeof(struct jointUser));

	modUser.balance = currUser.balance;
        if(!strcmp(currUser.status,"ACTIVE")  && (modUser.account_no==currUser.account_no)){
                strcpy(modUser.status,"ACTIVE");
                lseek(fd,(-1)*sizeof(struct jointUser),SEEK_CUR);
                int j=write(fd,&modUser,sizeof(struct jointUser));
                if(j!=0)        result=true;
                else            result=false;
        }

        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);

        close(fd);
        return result;
}

#endif
