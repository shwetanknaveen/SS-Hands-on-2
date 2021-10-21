#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
	mkfifo("myfifo",0666);
	char buf[101];
	while(1){
		int fd1 = open("myfifo",O_RDONLY);
		read(fd1,buf,sizeof(buf));
		printf("Message Read From The Pipe:: %s",buf);
		close(fd1);
	}
	return 0;
}