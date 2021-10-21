#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h>

#define PORT 12345

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int compare(const void* a, const void * b){
	return (*(int *)a - *(int *)b);
}

int main(int argc, char* argv[]){
	if(argc==1){
        printf("Run server using following command.\n./server [PORT NO]\n");
        return 0;
    }
	int _sockfd, _newSockfd, cli_addr_len, bufferLength;
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;
	printf("\n\n\t\t\tHI! THIS IS SERVER.\n");

	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_sockfd < 0){
		error("ERROR Opening Socket");
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=atoi(argv[1]); //reading port no from command line
	serv_addr.sin_addr.s_addr=INADDR_ANY;//INADDR_ANY;
	if (bind(_sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    	error("ERROR On Binding");
    }

    listen(_sockfd,1);

    while(1){
    	cli_addr_len = sizeof(cli_addr);
	    _newSockfd = accept(_sockfd, (struct sockaddr *) &cli_addr, &cli_addr_len);
	    if (_newSockfd < 0){
	        error("ERROR On Accept");
	    	exit(0);
	    }
	    
	    int count=0;
	    
	    recv(_newSockfd,&count,sizeof(int),0);
	    printf("Expecting %d Numbers To Sort\n",count);
	    
	    int *arr = malloc(sizeof(int)*count);
	    int i=0,num=0;
	    float sum=0;
	    for(;i<count;i++){
	    	recv(_newSockfd,&num,sizeof(int),0);	
	    	arr[i]=num;
	    	sum+=num;
	    }
	    printf("%d Numbers Received From Client.\n",i);
	    sleep(5);
	    printf("\nSum Of Numbers Is:: %g.\n",sum);
	    float avg = (sum/count);
	    printf("\nAverage Of Numbers Is:: %g.\n",avg);
	    
	    qsort(arr,count,sizeof(int),compare);
	    for(int i=0; i< count; i++){
	    	send(_newSockfd,&arr[i],sizeof(int),0);
	    }
	    printf("\n");
	
	    bufferLength = send(_newSockfd,&avg,sizeof(float),0);
	    if (bufferLength < 0){
	    	error("ERROR Writing To Socket");
	    	exit(0);
	    }
	    printf("Average Sent To Client\n");
	    close(_newSockfd);
	}
    return 0;
}

/*
run this code on a different terminal using following code
./33_tcpServerout.out 12345
we are giving 12345 as port no. on which server will interact
*/