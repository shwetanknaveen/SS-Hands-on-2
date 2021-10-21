#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

// Implementation of ls -l command
/*
Since child process is working on pipefd[1], i.e. write fd thus this ensures that child always runs prior to parent
Even if Parent tries to run first it is suspended as it is trying to read before ant write has happened.
*/
int main()
{
  int pipefd[2];
  pipe(pipefd);

  int process_id = fork();

  if(process_id == 0) //child
  {
    close(1); // Closing STDOUT, FD = 1, In order to output of ls -l go to pipefd[1] instead of STDOUT.
    fcntl(pipefd[1], F_DUPFD); // Duplicating using dup we will be assigned fd 1 as it's the lowest
    close(pipefd[0]); // Closing unnecessary opened FD's
    execlp("ls", "ls", "-l", NULL);
  }

  else
  {
    close(0); // Closing STDIN, FD = 0, In order to get input from pipefd[0] instead of STDIN.
    fcntl(pipefd[0], F_DUPFD); // Duplicating using dup we will be assigned fd 0 as it's the lowest
    close(pipefd[1]); // Closing unnecessary opened FD's
    execlp("wc","wc", NULL);
  }

  return 0;
}