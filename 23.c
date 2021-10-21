#define _GNU_SOURCE
#include <stdio.h>
#include <ulimit.h>
#include <fcntl.h>

int main(){
	unsigned long n = ulimit(4); //returns the max no of files that a calling process can open	
    //read about the function ulimit at https://man7.org/linux/man-pages/man3/ulimit.3.html
	printf("Max no of files a process can open %lu\n",n);

	int fd = open("myfifo",O_RDONLY|O_NONBLOCK);
	long pipe_size = (long)fcntl(fd, F_GETPIPE_SZ);// read about F_GETPIPE_SZ on https://man7.org/linux/man-pages/man7/pipe.7.html
	printf("Max size of a pipe %ld\n",pipe_size);
	return 0;
}