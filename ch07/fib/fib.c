#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,  char *argv[ ]) {
	pid_t childpid;             /* indicates process should spawn another     */
	int error;                  /* return value from dup2 call                */
	int fd[2];                  /* file descriptors returned by pipe          */
	int i;                      /* number of this process (starting with 1)   */
	int nprocs;                 /* total number of processes in ring          */ 

#define BUFSIZE 1024
	char buf[BUFSIZE];			/* buffer for reading fib */
	unsigned long a, b, c;

	/* check command line for a valid number of processes to generate */
	if ( (argc != 2) || ((nprocs = atoi (argv[1])) <= 0) ) {
		fprintf(stderr, "Usage: %s nprocs\n", argv[0]);
		return 1; 
	}  

	/* connect std input to std output via a pipe */
	if (pipe (fd) == -1) {      
		perror("Failed to create starting pipe");
		return 1;
	}
	if ((dup2(fd[0], STDIN_FILENO) == -1) ||
			(dup2(fd[1], STDOUT_FILENO) == -1)) {
		perror("Failed to connect pipe");
		return 1;
	}
	if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
		perror("Failed to close extra descriptors");
		return 1; 
	}        
	/* create the remaining processes */
	for (i = 1; i < nprocs;  i++) {
		if (pipe (fd) == -1) {
			fprintf(stderr, "[%ld]:failed to create pipe %d: %s\n",
					(long)getpid(), i, strerror(errno));
			return 1; 
		} 
		if ((childpid = fork()) == -1) {
			fprintf(stderr, "[%ld]:failed to create child %d: %s\n",
					(long)getpid(), i, strerror(errno));
			return 1; 
		} 
		/* for parent process, reassign stdout */
		if (childpid > 0)               
			error = dup2(fd[1], STDOUT_FILENO);
		/* for child process, reassign stdin */
		else                              
			error = dup2(fd[0], STDIN_FILENO);
		if (error == -1) {
			fprintf(stderr, "[%ld]:failed to dup pipes for iteration %d: %s\n",
					(long)getpid(), i, strerror(errno));
			return 1; 
		} 
		if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
			fprintf(stderr, "[%ld]:failed to close extra descriptors %d: %s\n",
					(long)getpid(), i, strerror(errno));
			return 1; 
		} 
		if (childpid)
			break;
	}                                               

	if ( i > 1 ) {
		/* FIXME error check */
		fgets(buf, BUFSIZE, stdin);
		fprintf(stderr, "buf %s\n", buf);
		a = atoi(strtok(buf, " "));
		b = atoi(strtok(NULL, " "));
		fprintf(stderr, "%lu %lu\n", a, b);
		c = a + b;
	}
	else {
		/* seed the ring */
		a = 1;
		b = 1;
		c = 1;
	}
	fprintf(stdout, "%lu %lu", b, c);

	/* say hello to the world */
	fprintf(stderr, "Process %d with PID %ld and parent PID %ld received %lu %lu and sent %lu %lu.\n", i, (long)getpid(), (long)getppid(), a, b, b, c);
	/* wait(NULL); */

	return 0; 

}     
