/*

A concurrent server accepts a client connection, delegates the connection to a child process of some kind, and immediately
signals its availability to receive the next client connection.
*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h>

#define MAX 256
#define READ			"0"
#define WRITE			"1"
#define PORT 12385
#define SYNACK 10

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int compare(const void* a, const void * b){
	return (*(int *)a - *(int *)b);
}

void doStuff(int _newSockfd){
	int count=0,bufferLength;
	    
    recv(_newSockfd,&count,sizeof(int),0);
    printf("Expecting %d nos to sort\n",count);
    
    int *arr = malloc(sizeof(int)*count);
    int i=0,num=0;
    float sum=0;
    for(;i<count;i++){
    	recv(_newSockfd,&num,sizeof(int),0);	
    	arr[i]=num;
    	sum+=num;
    }
    printf("%d nos received from client\n",i);
    sleep(5);
    printf("\nSum of nos is %g\n",sum);
    float avg = (sum/count);
    printf("\nAvg of nos is %g\n",avg);
    
    qsort(arr,count,sizeof(int),compare);
    for(int i=0; i< count; i++){
    	send(_newSockfd,&arr[i],sizeof(int),0);
    }
    printf("\n");

    bufferLength = send(_newSockfd,&avg,sizeof(float),0);
    printf("Sent avg to client\n");
    if (bufferLength < 0){
    	error("ERROR writing to socket");
    	exit(0);
    }
}

int main(int argc, char* argv[]){
    if(argc==0){
        printf("Run server using following command.\n./server [PORT NO]\n");
        return 0;
    }
	int _sockfd, _newSockfd, cli_addr_len;
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;
	char stream[MAX];
	char ack[10]={'\0'}, syn[10] = {'\0'};
	printf("Hi!!!This is server...\n");

	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_sockfd < 0){
		error("ERROR opening socket");
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=atoi(argv[1]); //read port no
	serv_addr.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY;
	if (bind(_sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    	error("ERROR on binding");
    }

    listen(_sockfd,1);

    while(1){
    	cli_addr_len = sizeof(cli_addr);
	    _newSockfd = accept(_sockfd, (struct sockaddr *) &cli_addr, &cli_addr_len);
	    if (_newSockfd < 0){
	        error("ERROR on accept");
	    	exit(0);
	    }

	    if(fork()==0){
            close(_sockfd);
	    	doStuff(_newSockfd);
	    }
	    else
	    
	    close(_newSockfd);
	}
    return 0;
}

/*
run this code on a different terminal using following code
./34_forkServerout.out 12345
we are giving 12345 as port no. on which server will interact
*/