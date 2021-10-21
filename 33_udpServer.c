#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define MAX 256
#define PORT 8090
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int compare(const void* a, const void * b){
    return (*(int *)a - *(int *)b);
}

int main(int argc, char* argv[]) {
    if(argc==1){
        printf("Run Server Using Following Command.\n./server [PORT NO]\n");
        return 0;
    }
    int udp_sock, cli_addr_len, bufferLength;
    struct sockaddr_in serv_addr, cli_addr;
    struct hostent *server;
    char stream[MAX];
    int myPort=atoi(argv[1]);
    char *hello = "Received 5 Numbers"; 
    cli_addr_len=sizeof(cli_addr);
    printf("Hi! This Is Server...\n");
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0){
        error("ERROR Opening Socket");
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(myPort);
    
    if (bind(udp_sock, (const struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR On Binding");
    }
    int len, n,count=5;
    while(1){
        n = recvfrom(udp_sock, (int *)&count, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr,
                    &len);
        
        printf("Client : %d Numbers To Sort And Average.\n", count);
        int A[count];
        float sum=0,avg=0;
        recvfrom(udp_sock, (int *)&A, sizeof(A), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
        for(int i=0;i<count;i++){
             sum+=A[i];
        }
        printf("\n%d Numbers Received From Client.\n",count);
        
        printf("\nSum of Numbers Is:: %g\n",sum);
        avg = (sum/count);
        printf("\nAverage of Numbers Is:: %g\n",avg);
        qsort(A,count,sizeof(int),compare);
        for(int i=0; i< count; i++){
            printf("%d ",A[i]);
        }
        int ack=0;
        ack=0;
        sendto(udp_sock,(const int*)&A,sizeof(A), MSG_CONFIRM, (const struct sockaddr *)&cli_addr, sizeof(cli_addr));
        printf("\nSorted Numbers Sent.\n");
     
        recvfrom(udp_sock, (int *)&ack, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);
        printf("%dSorted Numbers Received By Client.\n",ack);
        bufferLength = sendto(udp_sock,(const float*)&avg,sizeof(float), MSG_CONFIRM, (const struct sockaddr *)&cli_addr, sizeof(cli_addr));
        printf("\nSent Average To Client.\n");
        recvfrom(udp_sock, (int *)&ack, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &cli_addr, &len);   
    }
    return 0;
}

/*
run this code on a different terminal using following code
./33_udpServerout.out 12345
we are giving 12345 as port no. on which server will interact
*/