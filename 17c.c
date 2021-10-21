#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>


int main(void)
{
    int fd[2];

    pipe(fd);

    if (!fork()) {
        close(fd[0]);       /* close normal stdout */
        dup2(fd[1],1);   
        execlp("ls", "ls", "-l", (char *)0);
    } else {
        close(fd[1]);       /* close normal stdin */
        dup2(fd[0],0);   
        execlp("wc", "wc", (char *)0);
    }

    return 0;
}
