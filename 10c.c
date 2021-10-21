
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>


void handler(int nSignum, siginfo_t* si, void* vcontext){
    if(nSignum == SIGFPE)/* Erroneous arithmetic operation.  */
        printf("SIGFPE Encountered\n");
    exit(1);
}

int main() {

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;

    sigaction(SIGFPE, &action, NULL);//floating point exception

    int i = 0;
    int j = 2/i;//raising SIGFPE that is erroneous airitmatic operation signal

    return 0; 
}