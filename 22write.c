#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
	
	printf("Write data: ");
	char buf1[100];
	int fd = open("myfifo",O_WRONLY);
	fgets(buf1,sizeof(buf1),stdin);
	printf("%s",buf1);
	write(fd,buf1,strlen(buf1)+1);
	close(fd);
	return 0;
}

//run this code first....that is run ./22writeout.out first so that write end is opened first