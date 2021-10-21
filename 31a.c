#include <stdio.h> 
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex; //create a semaphore

void * thread(int num)
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
	sem_init(&mutex, 0, 1); // 0 means it is shared by threads of process and third parameter is initial value of the semaphore
    pthread_t t1,t2;
    int i1=1;
    int i2=2; 
    pthread_create(&t1,NULL,(void *)&thread,&i1); 
    // thread is the start routine... 
    //(second argument)the argument attr points to structure whose contents 
    //are used at thread creation time and when it is null than default attributes are set... 
    //and in the last argument the arg it is the thread's argument 
    //and as we are not passing anything here hence it is null.
 
    sleep(2); 
    pthread_create(&t2,NULL,(void *)&thread,&i2);  
    pthread_join(t1,NULL); 
    // that is the thread is joinable....
    //and hence it will wait for the exit status of the target thread

    pthread_join(t2,NULL); 
    sem_destroy(&mutex); //remove a semaphore

	return 0;
}
//compile this code as following
//gcc -pthread -o 31aout.out 31a.c

/*
       int sem_init(sem_t *sem, int pshared, unsigned int value);

       sem_init() initializes the unnamed semaphore at the address
       pointed to by sem.  The value argument specifies the initial
       value for the semaphore.

       The pshared argument indicates whether this semaphore is to be
       shared between the threads of a process, or between processes.

       If pshared has the value 0, then the semaphore is shared between
       the threads of a process, and should be located at some address
       that is visible to all threads (e.g., a global variable, or a
       variable allocated dynamically on the heap).

       If pshared is nonzero, then the semaphore is shared between
       processes, and should be located in a region of shared memory
       (see shm_open(3), mmap(2), and shmget(2)).  (Since a child
       created by fork(2) inherits its parent's memory mappings, it can
       also access the semaphore.)  Any process that can access the
       shared memory region can operate on the semaphore using
       sem_post(3), sem_wait(3), and so on.

       Initializing a semaphore that has already been initialized
       results in undefined behavior.
*/