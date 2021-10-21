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
    printf("How many numbers do you want to sort and average?:: ");
    scanf("%d",&count);
    
    printf("Enter %d numbers separated by a space and then press enter...\n",count);
    for(int i=0; i< count; i++){
        scanf("%d",&arr[i]);
    }
    
    tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//Socket of type SOCK_STREAM is  full-duplex byte streams
    /*
    Create a new socket of type TYPE in domain DOMAIN, using
    protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
    Returns a file descriptor for the new socket, or -1 for errors.
    Domain (AF – Address Family)
    AF_UNIX      for UNIX domain
    AF_INET      for Internet domain

    */
	if(tcp_sock < 0){
		error("ERROR Opening Socket");
	}


	_port=atoi(argv[1]); //reading port no from command line->first argument is port number of of server on which client has to interact
	server = gethostbyname(argv[2]); //reading loopback ip address from command line: 127.0.0.1
	bzero((char *) &serv_addr, sizeof(serv_addr));
    /*
    void bzero(void *s, size_t n);
    The bzero() function erases the data in the n bytes of the memory
    starting at the location pointed to by s, by writing zeros (bytes
    containing '\0') to that area.
    */

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    /*
    void bcopy(const void *src, void *dest, size_t n);
    The bcopy() function copies n bytes from src to dest.  The result
    is correct, even when both areas overlap.
    */
    serv_addr.sin_port = _port;


    /*
    The connect() system call connects the socket referred to by the
    file descriptor sockfd to the address specified by addr.  The
    addrlen argument specifies the size of addr.  The format of the
    address in addr is determined by the address space of the socket
    sockfd;
    */
    if (connect(tcp_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    {
    	error("ERROR Connecting");
    	exit(0);
    }
    
    bufferLength = send(tcp_sock,&count,sizeof(int),0);     
	for(int i=0; i< count; i++){
    	send(tcp_sock,&arr[i],sizeof(int),0);
    }
	
	if (bufferLength < 0){
         error("ERROR Writing To Socket");
    }  

	int *sorted_arr;
    float avg=0;
    for(int i=0; i< count; i++){
    	recv(tcp_sock,&arr[i],sizeof(int),0);
    }
    printf("Sorted Array:: ");
    for(int i=0; i< count; i++){
    	printf("%d ",arr[i]);
    }
    recv(tcp_sock,&avg,sizeof(float),0);
    printf("\nAverage of Numbers is:: %g\n",avg);
    return 0;
}

/*
Run this code as following
./33_tcpClientout.out 12345 172.16.130.244
where 12345 is the port number of server which was given by running serverfile as following
./33_tcpServerout.out 12345
and 172.16.130.244 is server IP address given by following command on server machine
hostname -I
*/