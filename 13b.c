
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void handler(){}

int main(int argc,char *argv[]){
    kill(atoi(argv[1]),SIGSTOP);
    return 0;
}
//run this program in another terminal
//get pidof 13a.c as following
//pidof ./13aout.out
//then run 13bout.out as following
//  ./13out.out pid
//as soon as this is run, 13aout.out is stopped