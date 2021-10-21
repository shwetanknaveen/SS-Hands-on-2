#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(){
    printf("catched SIGSEGV\n");
    exit(1);
}
int main(){
    
    if(signal(SIGSEGV, handler) == SIG_ERR) //SIGSEV -> signal for memory access violation
		printf("error while catching SIGSEGV\n");

    raise(SIGSEGV);//raising sigsegv so that it get caught by our handler
    return 0;
}