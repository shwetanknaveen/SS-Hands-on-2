#include <stdio.h> 
#include <sys/msg.h> 

struct msg_buffer { 
    long msg_type; 
    char msg_text[100]; 
} message; 
  
int main() 
{ 
	int msqid;
    printf("Enter msg queue id ");
    scanf("%d",&msqid);//enter the msg queue id as the id which was generated in 26.c which can be checked with ipcs -q
    msgrcv(msqid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT); // Last second argument is 1 which indicates message type i.e first message in the queue if type 1
  															 //Last argument can be '0' or IPC_WAIT. 0 means wait.
    printf("Data Received is : %s \n",  message.msg_text); 
  
    return 0; 
} 