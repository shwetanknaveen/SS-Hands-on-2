#include <stdio.h>
#include <sys/msg.h>
  
struct msg_buffer { 
    long msg_type; 
    char msg_text[100]; 
} message; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
    key = ftok("msg_queue", 65); 

    msgid = msgget(key, 0666 | IPC_CREAT); 
    message.msg_type = 1; 
  
    printf("Write Data : "); 
    gets(message.msg_text); 
  
    msgsnd(msgid, &message, sizeof(message.msg_text), 0); //0 means wait if the message queue is already full
                                                          //https://linux.die.net/man/2/msgsnd
  
    printf("Data send is : %s \n", message.msg_text); 
  
    return 0; 
} 

/*
ipcs -q 
shows following output
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          shwetank   666        100          1  
*/