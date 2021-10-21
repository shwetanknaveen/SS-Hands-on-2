#include <stdio.h> 
#include <sys/shm.h> 
  
int main() 
{ 
    key_t key = ftok("shmfile",65); 
  
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Data read from memory: %s\n",str); 
      
    shmdt(str); 
    
    shmctl(shmid,IPC_RMID,NULL); //remove the shared memory... mark the segment to be destroyed. 
    							 // The segment will  actually be  destroyed  only after the last process detaches it
     
    return 0; 
} 