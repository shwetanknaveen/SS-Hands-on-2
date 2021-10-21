#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *threadhandler(int *count){
	printf("I am thread %d\n",(*count+1));
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
//Video reference for creation and joining of threads - https://www.youtube.com/watch?v=uA8X5zNOGw8
//compile this code with following command
//gcc -pthread -o 06out.out 06.c
//https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux