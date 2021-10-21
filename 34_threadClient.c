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
#define PORT 12345

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char* argv[]){
    if(argc==0){
        printf("Run server first.\n\nRun client using following command.\n./client [PORT NO] [SERVER IP ADDR.]\n");
        return 0;
    }
	int tcp_sock, _port, bufferLength;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int arr[MAX];
	int count = 0;
    
    printf("Hi!!!This is client...\n");
    printf("How many numbers do you want to sort and average?\n");
    scanf("%d",&count);
    
    printf("Enter %d numbers separated by a space and then press enter...\n",count);
    for(int i=0; i< count; i++){
        scanf("%d",&arr[i]);
    }
    
    tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(tcp_sock < 0){
		error("ERROR opening socket");
	}

	_port=atoi(argv[1]);
	server = gethostbyname(argv[2]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = _port;

    if (connect(tcp_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    {
    	error("ERROR connecting");
    	exit(0);
    }
    
    bufferLength = send(tcp_sock,&count,sizeof(int),0);     
	for(int i=0; i< count; i++){
    	send(tcp_sock,&arr[i],sizeof(int),0);
    }
	
	if (bufferLength < 0){
         error("ERROR writing to socket");
    }
    
	int *sorted_arr;
    float avg=0;
    
    for(int i=0; i< count; i++){
    	recv(tcp_sock,&arr[i],sizeof(int),0);
    }
    printf("Sorted Array - ");
    for(int i=0; i< count; i++){
    	printf("%d ",arr[i]);
    }
    recv(tcp_sock,&avg,sizeof(float),0);
    printf("\nAvg of nos is- %g\n",avg);
    sleep(3);
    return 0;
}

/*
compile this code as following
gcc -pthread -o 34_threadClientout.out 34_threadClient.c

Run this code as following
./34_threadClientout.out 12345 172.16.130.244
where 12345 is the port number of server which was given by running serverfile as following
./33_threadServerout.out 12345
and 172.16.130.244 is server IP address given by following command on server machine
hostname -I

*/

