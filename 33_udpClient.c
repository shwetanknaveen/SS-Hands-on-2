#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define PORT 8090
 
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char* argv[]) {
    if(argc==0){
        printf("Run server first.\n\nRun client using following command.\n./client [PORT NO]\n");
        return 0;
    }
    int _sock;
    char buffer[sizeof(int)];
    char *hello = "Hello from client";
    struct sockaddr_in serv_addr;
    int s_size=sizeof(serv_addr),_port;

    if ( (_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    memset(&serv_addr, 0, sizeof(serv_addr));
    _port = atoi(argv[1]); //reading port no from command line
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    int n, len,count=5;
    printf("Hi!!!This is client...\n");
    printf("Enter no of nos to sort and avg...\n");
    scanf("%d",&count);
    
    printf("Enter %d numbers press enter...\n",count);
    int A[count];
    for(int i=0; i< count; i++){
        scanf("%d",&A[i]);
    }
    
    n = sendto(_sock, (const int*)&count, sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    n = sendto(_sock,(const int*)&A,sizeof(A), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (n < 0){
         error("ERROR writing to socket");
    }
    printf("Nums sent\n");
    

    float avg = 0;
    int B[count];
    int ack = 1;
    printf("\nWaiting for nums\n");
    recvfrom(_sock,(int *)&B,sizeof(B), MSG_WAITALL, (struct sockaddr * )&serv_addr, &s_size);
    printf("\nSorted Array - ");
    for(int i=0; i< count; i++){
        printf("%d ",B[i]);
    }
    sendto(_sock,(const int*)&ack,sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    recvfrom(_sock,(float *)&avg,sizeof(float), MSG_WAITALL, (struct sockaddr * )&serv_addr, &s_size);
    printf("\nAverage Of Numbers Is:: %g\n",avg);
    printf("\n");
    close(_sock);
    return 0;
}
/*
Run this code as following
./33_udpClientout.out 12345 172.16.130.244
where 12345 is the port number of server which was given by running serverfile as following
./33_udpServerout.out 12345
and 172.16.130.244 is server IP address given by following command on server machine
hostname -I
*/