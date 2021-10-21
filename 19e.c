#include <sys/stat.h>
       
int main(){

	char *file = "FIFO_FILE_MKFIFO";
	mkfifo(file, 0666);
	return 0;
}
//POSIX recommends mkfifo() for creation of fifo file