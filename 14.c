
#include<stdio.h>
#include<unistd.h>

int main(){
	char *s = "Hello World";
	char s1[12];
	int fd[2] = {0,1};
	pipe(fd);
	printf("%d %d\n",fd[0],fd[1]);
	write(fd[1],s,12);
	read(fd[0],s1,12);
	printf("%s\n",s1);
    return 0;
}