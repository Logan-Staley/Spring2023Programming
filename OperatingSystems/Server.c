#include "unpipc.h"
#include <fcntl.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
void server(int, int);

int main(int argc, char **argv)
{ int readfd, writefd;
		pid_t childpid;
/* create two FIFOs; OK if they already exist */
		if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
			err_sys("can't create %s", FIFO1);
		if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
			unlink(FIFO1);
			err_sys("can't create %s", FIFO2);
		}
		readfd = Open(FIFO1, O_RDONLY, 0);
		writefd = Open(FIFO2, O_WRONLY, 0);
		server(readfd, writefd);
		exit(0);
}
