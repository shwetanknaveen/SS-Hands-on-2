#include <stdio.h> 
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex; //create semaphore

void *thread(int num)
{
    printf("Above Critical Section For Thread:: %d.\n",num); 
    sem_wait(&mutex); //P or Wait
    printf("I am Critical Section For Thread:: %d.\n",num); 
    sleep(4);
    sem_post(&mutex); // V or Signal
    printf("Below Critical Section For Thread:: %d.\n\n",num);
}

int main(int argc, char const *argv[])
{
    int i1=1;
    int i2=2;
    int i3=3;
	sem_init(&mutex, 0, 2); //last argument is the initial value of the semaphore
    pthread_t t1,t2,t3; 
    pthread_create(&t1,NULL,(void *)&thread,&i1); 
    sleep(2); 
    pthread_create(&t2,NULL,(void *)&thread,&i2); 
    sleep(2); 
    pthread_create(&t3,NULL,(void *)&thread,&i3); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    pthread_join(t3,NULL); 
    sem_destroy(&mutex); //remove a semaphore

	return 0;
}