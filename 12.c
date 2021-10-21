
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(){
    printf("parent is getting killed");
}

int main(){
    pid_t pid, ppid;
    ppid = getpid();//process pid
    printf("ppid = %d\n", ppid);
    pid = fork();
    if((pid) == 0){ //for child
        sleep(2); 
        kill(ppid, SIGKILL); //create orphan process ,ppid contains pid of parent 
    }
    else{//for parent
    	printf("%d %d ",ppid, pid);//for parent pid will contain the pid of child returned by fork()
    	
        if(signal(SIGKILL,handler) == SIG_ERR)
        	printf("\ncan't catch SIGKILL\n");
        
        sleep(5); 
    }
    return 0;
}