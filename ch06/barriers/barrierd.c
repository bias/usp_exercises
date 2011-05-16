#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <emalloc.h>

#define FOREVER 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP | S_IWOTH)

int main(int argc, char *argv[]) { 
	char *request_name;
	char request_s[] = ".request";
	char *release_name;
	char release_s[] = ".release";
	char *buf;
	int size;
	int amount, total_amount;
	int requestfd, releasefd;
	int exit_status = 0;

	if ( argc != 3 ) {
		fprintf(stderr, "Usage: %s name size", argv[0]);	
		return 1;
	}
	
	size = atoi(argv[2]);
	buf = emalloc(size);

	request_name = emalloc(strlen(argv[1])+strlen(request_s)+1);
	strcat(strcpy(request_name, argv[1]), request_s);

	release_name = emalloc(strlen(argv[1])+strlen(release_s)+1);
	strcat(strcpy(release_name, argv[1]), release_s);

	if ( (mkfifo(request_name, FIFO_PERMS) == -1) && (errno != EEXIST) ) {
		perror("Failed to create request FIFO");
		return 1;
	}
	if ((mkfifo(release_name, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("Failed to create release FIFO");
		/* remove FIFO we created above */
		if (unlink(request_name) == -1) {
			perror("Failed to unlink request FIFO");
		}
		return 1;
	}

	while ( FOREVER ) {

		if ((requestfd = open(request_name, O_RDONLY)) == -1) {
			perror("Failed to open request FIFO");
			exit_status = 1;
			break; /* try to unlink FIFOs before exit */
		}
		total_amount = 0;
		while ( (amount = read(requestfd, buf, size)) != -1 && (total_amount += amount) < size ) ;
		if ( amount == -1 ) {
			perror("Failed to read");
			return 1;
		}
		while ( close(requestfd) == -1 && errno == EINTR ) ;
		
		if ((releasefd = open(release_name, O_WRONLY)) == -1) {
			perror("Failed to open release FIFO");
			exit_status = 1;
			break; /* try to unlink FIFOs before exit */
		}
		total_amount = 0;
		while ( (amount = write(releasefd, buf, size)) != -1 && (total_amount += amount) < size ) ;
		if ( amount == -1 ) {
			perror("Failed to write");
			return 1;
		}
		while ( close(releasefd) == -1 && errno == EINTR ) ;

	}

	if (unlink(request_name) == -1) {
		perror("Failed to unlink request FIFO");
		exit_status = 1;
	}
	if (unlink(release_name) == -1) {
		perror("Failed to unlink release FIFO");
		exit_status = 1;
	}

	return exit_status; 
}
