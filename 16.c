
#include<stdio.h>
#include<unistd.h>

int main(){
	int fd1[2],fd2[2];      //fd1[0]->Reading end of pipe-1; fd1[1]-> Writing end of pipe-1
                            //fd2[0]->Reading end of pipe-2; fd2[1]-> Writing end of pipe-2
	char buffer[70],reader[70];
	pipe(fd1);
	pipe(fd2);
	
    if(fork() != 0){//this is parent as for parent, fork() returns non zero value which is process id of the child created
        close(fd2[0]);//close reading end of pipe 2
		close(fd1[1]);//close writing end of pipe 1
		
        printf("This is child. Message to parent is: ");	
		read(fd1[0],reader,70);//reading from pipe 1	
		printf("%s\n",reader);		
		
        printf("This is Parent. Enter message to child: ");
		scanf(" %[^\n]s",buffer);
		write(fd2[1],buffer,70);	//writing to pipe 2

		close(fd1[0]);
		close(fd2[1]);
	}
	else{ //in the child process
        close(fd1[0]);//close reading end of pipe 1
		close(fd2[1]);//close writing end of pipe 2
		
        printf("This is Child.Enter Message to parent: ");
		scanf(" %[^\n]s",buffer);
		write(fd1[1],buffer,70);	//writing to pipe 1
		printf("This is parent. Message to child is: ");	
		read(fd2[0],reader,70);	//reading from pipe 2
		printf(" %s\n",reader);		

		close(fd2[0]);
		close(fd1[1]);
	}
	return 0;
}