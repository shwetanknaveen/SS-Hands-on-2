#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
	char buff[100];
	//mkfifo("myfifo",0666);
	unsigned int fd = open("myfifo",O_RDONLY);
	fd_set rfds;
    struct timeval tv;
    int retval;
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /* Wait up to ten seconds. */
    tv.tv_sec = 10;
	tv.tv_usec = 0;
    //printf("%d",2);
    printf("%s","Waiting on select\n");
    retval = select(fd+1, &rfds, NULL, NULL, &tv);
    
    /* Don't rely on the value of tv now! */
    if (retval == -1)
        perror("select()");
    else if (retval){
        printf("Data is available now.\n");
        read(fd,&buff,sizeof(buff));
        printf("Data available is: %s\n", buff);
    }

    /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within ten seconds.\n");

	return 0;
}
//run writeout.out code first....that is run ./22writeout.out first so that write end is opened first