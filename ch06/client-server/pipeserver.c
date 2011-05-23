#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

#include <restart.h>

#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)

int main (int argc, char *argv[]) {
	time_t curtime;
	char buf[PIPE_BUF];
	int requestfd, replyfd;
	int len;

	/* name of server fifo is passed on the command line */
	if (argc != 2) {    
		fprintf(stderr, "Usage: %s fifoname > logfile\n", argv[0]);
		return 1; 
	}

	/* create a named pipe to handle incoming requests */
	if ((mkfifo(argv[FIFOARG], FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("Server failed to create request FIFO");
		return 1; 
	}
	fprintf(stderr, "Server created FIFO: %s\n", argv[FIFOARG]);

	/* open a read/write communication endpoint to the pipe */
	if ((requestfd = open(argv[FIFOARG], O_RDWR)) == -1) {
		perror("Server failed to open request FIFO");
		return 1;
	}

	while ( 1 ) {
		r_read(requestfd, buf, PIPE_BUF); 
		fprintf(stderr, "Server got request pid: %s\n", buf);

		if ((replyfd = open(buf, O_WRONLY)) == -1) {
			perror("Server failed to open reply FIFO");
			return 1;
		}
		fprintf(stderr, "Server opened request pipe: %s\n", buf);

		curtime = time(NULL);
		snprintf(buf, PIPE_BUF, "%d: %s", (int)getpid(), ctime(&curtime));
		len = strlen(buf);
		if ( r_write(replyfd, buf, len) != len ) {
			perror("Server failed to write to request FIFO"); 
			return 1;
		}
		fprintf(stderr, "Server wrote reply: %s", buf); /* ctime includes newline */

		r_close(replyfd);
	}

	r_close(requestfd);
	unlink(argv[FIFOARG]);

	return 1; 
}
