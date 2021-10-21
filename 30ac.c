#include <stdio.h> 
#include <sys/shm.h> 
  
int main() 
{ 
    key_t key = ftok("shmfile",65); //convert pathname  and a project identifier to system v ipc key
  
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    printf("Shared memory id: %d\n",shmid);
  
    char *str = (char*) shmat(shmid,(void*)0,0); //attaches the shared memory segment to the address space of the calling process
  
    printf("Write Data : "); 
    gets(str); 
  
    printf("Data written in shared memory: %s\n",str); 
      
    shmdt(str); //detaches the shared memory segment but not removed

  
    return 0; 
} 