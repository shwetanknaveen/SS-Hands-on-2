#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

sem_t mutex; 

void *thread(){
	//wait
	sem_wait(&mutex); 
    printf("\nEntered..\n");

    char buff[20];
    int fd=open("ticket",O_RDWR);
    read(fd,buff,20);
    int ticket = atoi (buff);
    ticket++;
    printf("Ticket number %d\n",ticket);
    lseek (fd,0,0);
    sprintf(buff, "%d", ticket);
    write(fd,buff,strlen(buff));
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&mutex);
    /*
       sem_post() increments (unlocks) the semaphore pointed to by sem.
       If the semaphore's value consequently becomes greater than zero,
       then another process or thread blocked in a sem_wait(3) call will
       be woken up and proceed to lock the semaphore.

    */
}

int main(int argc, char const *argv[])
{
	sem_init(&mutex, 0, 1); 
    pthread_t t1,t2; 
    pthread_create(&t1,NULL,thread,NULL); 
    pthread_create(&t2,NULL,thread,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&mutex); 

	return 0;
}