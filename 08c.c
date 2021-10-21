#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void handler(){
    printf("catched SIGFPE\n");
    exit(1);
}
int main(){
    
    if(signal(SIGFPE, handler) == SIG_ERR)  //Erroneous airthmatic operations
		printf("error while catching SIGFPE\n");

    int y = 1/y;//division by 0 will raise SIGFPE
    return 0;
}