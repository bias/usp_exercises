#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <time.h>*/
#include <unistd.h>
#include <sys/stat.h>

#include <restart.h>

#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)

int main (int argc, char *argv[]) {
	/*time_t curtime;*/
	pid_t pid;
	int len;
	char buf[PIPE_BUF];  
	char pid_name[BUFSIZ];  
	int requestfd, replyfd;             

	/* setup pid string */
	pid = getpid();
	if ( snprintf(pid_name, BUFSIZ, "%i", (int)pid) == -1 ) {
		perror("Client failed to write pid to buffer");
		return 1;
	}

	/* name of client fifo is passed on the command line */
	if (argc != 2) {  
		fprintf(stderr, "Usage: %s fifoname\n", argv[0]);
		return 1; 
	}

	/* open request pipe */
	if ((requestfd = open(argv[FIFOARG], O_WRONLY)) == -1) {
		perror("Client failed to open request FIFO");
		return 1; 
	}
	fprintf(stderr, "Client opened request FIFO: %s\n", argv[FIFOARG]);

	/* create reply pipe and open for reading */
	if ((mkfifo(pid_name, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("Client failed to create reply FIFO");
		return 1; 
	}
	fprintf(stderr, "Client created reply FIFO: %s\n", pid_name);

	snprintf(buf, PIPE_BUF, "%d", (int)pid);
	len = strlen(buf);
	if (r_write(requestfd, buf, len) != len) {
		perror("Client failed to write to request FIFO");
		return 1;
	}
	fprintf(stderr, "Client wrote request: %s\n", buf);

	if ((replyfd = open(pid_name, O_RDONLY)) == -1) {
		perror("Client failed to open reply FIFO");
		return 1;
	}
	fprintf(stderr, "Client opened reply FIFO: %s\n", pid_name);

	r_read(replyfd, buf, PIPE_BUF); 
	fprintf(stderr, "Client got reply: %s", buf); /* ctime includes newline */

	r_close(replyfd);
	unlink(pid_name);
	r_close(requestfd);
	
	return 0; 
}
