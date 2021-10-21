#include<stdio.h>
#include<signal.h>
#include <string.h>
#include<stdlib.h>

void handler(int nSignum, siginfo_t* si, void* vcontext){
	printf("Segmentation fault Encountered\n");
	exit(1);
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;

	sigaction(SIGSEGV, &action, NULL);

    int* x = 0;//to cause segmentation fault . Here x is made null
  	int y = *x;//we are dereferencing null pointer
    
    return 0;
}