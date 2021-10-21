
#include<stdio.h>
#include<unistd.h>

int main() {
	int fd[2]={0,1};
	int msg = 0;

	pipe(fd);
	if(fork() != 0){//for parent as for parent fork() returns the pid of created child
	
    	// parent: writing only, so close read-descriptor.
		close(fd[0]);
        printf("write int to send\t");
		//msg = 100;
        scanf("%d",&msg);
		write(fd[1], &msg, sizeof(msg));
		printf("Parent(%d) send msg: %d\n", getpid(), msg);

		// close the write descriptor
		close(fd[1]);

	}else{//for child fork() returns 0

		// child: reading only, so close the write-descriptor
		close(fd[1]);

		read(fd[0], &msg, sizeof(msg));
		printf("Child(%d) received msg: %d\n", getpid(), msg);

		// close the read-descriptor
		close(fd[0]);
	}
	return 0;
}