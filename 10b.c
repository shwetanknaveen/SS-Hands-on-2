
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>


void handler(int signum){
	if(signum == SIGINT)
		printf("recieved SIGINT\n");
	
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO;
	action.sa_handler = handler;

	sigaction(SIGINT, &action, NULL);
    //press ctrl +c to cause SIGINT
	while(1)
	    sleep(1);
    return 0;

    /*
    Killing the process
    press ctrl+z to sleep the process the do following to kill it
    pidof 10b.c
    kill -9 "pidof"
    The kill -9 command sends a SIGKILL signal indicating to a service to shut down immediately. 
    An unresponsive program will ignore a kill command, but it will shut down whenever a kill -9 command is issued.
    */
}