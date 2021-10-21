#include <stdio.h> 
#include <sys/msg.h> 

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
	int msqid;
    printf("Enter msg queue id ");
    scanf("%d",&msqid); 
    struct msqid_ds msqid_ds, *buf;
	buf = &msqid_ds;

    msgctl(msqid, IPC_STAT,buf);

    printf("Permission is : %o \n",  buf->msg_perm.mode);

	buf->msg_perm.mode = 0644;

	msgctl(msqid, IPC_SET,buf);
   
    msgctl(msqid, IPC_STAT,buf);
  
    printf("Permission changed to : %o \n",  buf->msg_perm.mode); 
  
    return 0; 
} 