#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long long rdtsc()
{
	unsigned long long dst;
	__asm__ __volatile__ ("rdtsc":"=A" (dst)); 
	return dst;
}

void main()
{
	int i = 100, nano;
	unsigned long long int start, end;
	start = rdtsc();
	
	while(i--)
		getpid();
		
	end = rdtsc();
	nano = (end-start)/2.20;  //lscpu |more 2.20 is my CPU frequency in GHz
	
	printf("Time elapsed for the 100 getpid() calls =  %d nano seconds\n", nano);
	
}