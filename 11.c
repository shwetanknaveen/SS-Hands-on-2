
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

int main(){

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = 0;
	action.sa_handler = SIG_IGN;//to ignore
	sigaction(SIGINT, &action, NULL);
	printf("Pressing Ctrl-C has no effect....\n");
	sleep(5);

	action.sa_handler = SIG_DFL;//to set back to default
	sigaction(SIGINT, &action, NULL);
	printf("Pressing Ctrl-C has effect now....\n");
	
	sleep(5);
    return 0;
}