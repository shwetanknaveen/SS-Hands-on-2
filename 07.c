#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *threadhandler(int *count){
	printf("I am thread %d\n",(*count+1));
    printf("The ID of current thread is: %u\n", (unsigned int)pthread_self()); //this gives id of the thread.
    /*
        Since only one of the created threads runs at a time, every new one gets the same ID as the one that finished 
        before, i.e. the IDs are simply reused
        https://stackoverflow.com/a/23980693
    */
	return NULL;
}
int main() {
    pthread_t thr;
    int i;

	for(i=0;i<3;i++) {
	   pthread_create(&thr, NULL ,(void *)&threadhandler , &i);
       pthread_join(thr, NULL);
       /*
       extern int pthread_join (pthread_t __th, void **__thread_return);
       Make calling thread wait for termination of the thread TH.  The
       exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
       is not NULL.
       */
	   sleep(2);
	}
    return 0;
}
//compile the given code with following command
//gcc -pthread -o 07out.out 07.c
