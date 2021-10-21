#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main(){
  
    signal(SIGINT, SIG_IGN);//SIG_IGN ignore the signal
	printf("Pressing Ctrl-C has no effect....\n");
	sleep(5);

	printf("\n\n\nPressing Ctrl-C has effect now....\n");
	signal(SIGINT, SIG_DFL);//setting back to the default
	sleep(5);
    return 0;
}