#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <atomic_logger.h>

#define BUFSIZE 1024
#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define CREATE_PERMS (S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH)

int main  (int argc, char *argv[]) {
	char buf[BUFSIZE];
	pid_t childpid = 0; 
	int fd;
	int i, n;

	if (argc != 4){       /* check for valid number of command-line arguments */
		fprintf (stderr, "Usage: %s processes log_file atomic_file\n", argv[0]);
		return 1;
	}     
	/* open the log file before the fork */
	fd = open(argv[2], CREATE_FLAGS, CREATE_PERMS);
	if (fd < 0) {
		perror("Failed to open file");
		return 1;
	}
	n = atoi(argv[1]);                              /* create a process chain */
	for (i = 1; i < n; i++)
		if (childpid = fork())
			break;
	if (childpid == -1) {
		perror("Failed to fork");
		return 1;
	}     

	/* open atomic log after fork */
	if (atomic_log_open(argv[3]) == -1) {
		fprintf(stderr, "Failed to open log file");
		return 1;
	}

	/* write twice to the common log file */
	sprintf(buf, "i:%d process:%ld ", i, (long)getpid());
	write(fd, buf, strlen(buf));
	atomic_log_string(buf);

	sleep(1);

	sprintf(buf, "parent:%ld child:%ld\n", (long)getppid(), (long)childpid);
	write(fd, buf, strlen(buf));
	atomic_log_string(buf);

	/* atomic_log_printf("i:%d process:%ld parent:%ld child:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid); */
	if ( atomic_log_send() == -1 ) {
		fprintf(stderr, "Failed to send to log file");
		return 1;
	}
	atomic_log_close();

	return 0;
}
