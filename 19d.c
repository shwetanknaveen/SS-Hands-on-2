#include <sys/stat.h>

int main(){

	char *file = "FIFO_FILE_MKNOD";
	mknod(file, S_IFIFO | 0666, 0);// mknod is used for block or chracter special files.
								   //mknod create a special or ordinary file
	return 0;
}

//POSIX recommends mkfifo() for creation of fifo file