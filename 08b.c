#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(){
    printf("\nCaught SIGINT\n");
    //press ctrl+c to raise SIGINT signal
    //press ctrl+z to sleep the process the do following to kill it
    //pidof 08b.c
    //kill -9 "pidof"
    //The kill -9 command sends a SIGKILL signal indicating to a service to shut down immediately. 
    //An unresponsive program will ignore a kill command, but it will shut down whenever a kill -9 command is issued.

    /*
        ctrl +c vs ctrl +z
        Ctrl + C is used to kill a process with signal SIGINT , in other words it is a polite kill . Ctrl + Z is used to 
        suspend a process by sending it the signal SIGTSTP , which is like a sleep signal, that can be undone and the process 
        can be resumed again.
    */
}
int main(){
    
    if(signal(SIGINT, handler) == SIG_ERR) /*
    The SIGINT signal is sent to a process by its controlling terminal when a user wishes to interrupt the process.
    This is typically initiated by pressing Ctrl-C, but on some systems, the "delete" character or "break" key can be used.
    The SIGKILL signal is sent to a process to cause it to terminate immediately (kill)
    */
		printf("error while catching SIGINT\n");

    while(1);    
    return 0;
}