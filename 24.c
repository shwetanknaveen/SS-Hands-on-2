#include <stdio.h>
#include <sys/msg.h> 
int main() 
{ 
	key_t key =ftok('.','a');//convert a path name and project identifier to system V style ipc key 
	int msgid = msgget(key,0666 | IPC_CREAT);

	printf("Key = 0x%0x\n",key);//hexadecimal format
	printf("Msgid = %d\n", msgid);


	return 0; 
} 