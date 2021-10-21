#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
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

    signal(SIGPROF,message);/*SIGPROF This signal typically indicates 
                                            expiration of a timer that measures both CPU time used by the current process,
                                            and CPU time expended on behalf of the process by the system. Such a timer is 
                                            used to implement code profiling facilities, hence the name of this signal.
                                            In software engineering, profiling is a form of dynamic program analysis that measures, for example, the space or time 
                                            complexity of a program, the usage of particular instructions, or the frequency and duration of function calls.
                                            */

    int r = setitimer(ITIMER_PROF,&i,NULL);//third parameter is old itimerval
                                            
    while(1);
    return 0;
}