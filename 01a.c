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
    t2.tv_sec=3;
    t2.tv_usec=0;
    i.it_interval=t1; //t1 provides interval. After alarming, after what time it has to happen again 
    i.it_value=t2; //t2 is for when to start timer

    signal(SIGALRM,message);//message is signal handler, SIGALRM is sent when real or clock time elapses. SIGVTALRM is sent when CPU time used by the process elapses.
    setitimer(ITIMER_REAL,&i,NULL);//ITIMER_REAL -> Timer runs only when the process is executing
    while(1);//consuming CPU time
    return 0;
}