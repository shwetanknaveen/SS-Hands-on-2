#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<stdlib.h>

void message(){
    static int s=0;
    printf("%d time interval\n",s++);
}

int main(){
    struct timeval t1,t2;
    struct itimerval i;
    t1.tv_sec=10;
    t1.tv_usec=0;
    t2.tv_sec=1;
    t2.tv_usec=0;
    i.it_interval=t1; //t1 provides interval 
    i.it_value=t2; //t2 is for when to start timer

    signal(SIGVTALRM,message);//SIGALRM is sent when real or clock time elapses. SIGVTALRM is sent when CPU time used by the process elapses.
    int r = setitimer(ITIMER_VIRTUAL,&i,NULL);//Timers run when the process is executing and when the system is executing on behalf of the process.  
    while(1);
    return 0;
}