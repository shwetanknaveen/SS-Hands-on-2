#include <stdio.h>
#include <sys/msg.h> 

int main() 
{ 
	int msqid;
	struct msqid_ds msqid_ds, *buf;
	buf = &msqid_ds;
	printf("Enter msqid: ");
	scanf("%d",&msqid);
	msgctl(msqid, IPC_STAT,buf);    //IPC_STAT	2		 Get `ipc_perm' options.  perm->permissions
	
	printf ("The access permissions = 0%o",buf->msg_perm.mode);
	printf ("\nThe USER ID = %d\n",buf->msg_perm.uid);
	printf ("The GROUP ID = %d\n",buf->msg_perm.gid);
	printf ("The msg_qbytes = %lu\n",buf->msg_qbytes);
	printf ("Time of last msg sent = %lu\n",buf->msg_stime);
	printf ("Time of last msg receive = %lu\n",buf->msg_rtime);
	printf ("Time of last msg change = %lu\n",buf->msg_ctime);
	printf ("Current number of bytes in queue = %lu\n",buf->__msg_cbytes);
	printf ("Current number of messages in queue = %lu\n",buf->msg_qnum);
	printf ("Maximum number of bytes allowed  = %lu\n",buf->msg_qbytes);
	printf ("Pid of last message sent = %d\n",buf->msg_lspid);
	printf ("Pid of last message received = %d\n",buf->msg_lrpid);

	return 0; 
} 