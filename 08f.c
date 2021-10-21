#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/time.h>

void handler(){
    printf("catched SIGALRM\n");
    exit(1);
}
int main(){
    

    if(signal(SIGVTALRM, handler) == SIG_ERR)//SIGALRM is sent when real or clock time elapses. SIGVTALRM is sent when 
                                            //CPU time used by the process elapses.
		printf("error while catching SIGALRM\n");
	
    //alarm(1);
    struct itimerval timer;
	timer.it_value.tv_sec = 2;
 	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;
    setitimer (ITIMER_VIRTUAL, &timer, NULL);

   	while(1);
    return 0;
}