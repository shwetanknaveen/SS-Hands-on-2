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
		int fd = open("myfifo",O_WRONLY);
		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,strlen(buf)+1);
		printf("Message Written To The Pipe.\n");
		close(fd);
	}
	return 0;
}