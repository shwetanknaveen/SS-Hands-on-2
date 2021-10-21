#include <stdio.h> 
#include <sys/msg.h> 
  
int main() 
{ 
    int msqid; 
    printf("Enter msg queue id to remove ");
    scanf("%d",&msqid); 
  
    msgctl(msqid, IPC_RMID, NULL);  

    printf("Removed\n");
  
    return 0; 
} 