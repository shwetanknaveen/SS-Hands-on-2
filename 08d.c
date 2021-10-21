#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handler(){
    printf("catched SIGALRM\n");
    exit(1);
}
int main(){
    

    if(signal(SIGALRM, handler) == SIG_ERR)
		printf("error while catching SIGALRM\n");
	
    alarm(1);//raising SIGALRM signal
	while(1){
		pause();
	}

    return 0;
}