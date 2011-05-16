#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <emalloc.h>
#include <barrier.h>

#define FOREVER 1

int waitatbarrier(char *name) {
	char *request_name;
	char request_s[] = ".request";
	char *release_name;
	char release_s[] = ".release";
	int requestfd, releasefd;
	char buf[1];
	int size = 1;

	buf[0] = 'x';
	
	request_name = emalloc(strlen(name)+strlen(request_s)+1);
	strcat(strcpy(request_name, name), request_s);

	release_name = emalloc(strlen(name)+strlen(release_s)+1);
	strcat(strcpy(release_name, name), release_s);

	if ((requestfd = open(request_name, O_WRONLY)) == -1) {
		perror("Failed to open request FIFO");
		return -1;
	}
	while ( write(requestfd, buf, size) < size && errno == EINTR ) ;
	while ( close(requestfd) == -1 && errno == EINTR ) ;
	
	if ((releasefd = open(release_name, O_RDONLY)) == -1) {
		perror("Failed to open release FIFO");
		return -1;
	}
	while ( read(releasefd, buf, size) < size && errno == EINTR ) ;
	while ( close(releasefd) == -1 && errno == EINTR ) ;

	return 0;
}
