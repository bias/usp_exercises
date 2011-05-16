#include <stdio.h>
#include <sys/stat.h>

#define FIFO_PERMS (S_IRWXU, S_IWGRP, S_IWOTH)

int main(int argc, char *argv[]) { 
	char *request_name;
	char request_s[] = ".request";
	char *release_name;
	char release_s[] = ".release";
	char size;

	if ( argc != 3 )
		fprintf(stderr, "Usage: %s name size", argv[0]);	
	

	request_name = emalloc(strlen(argv[1])+strlen(request_s)+1);
	strcat(strcpy(request_name, argv[1]), request_s);

	release_name = emalloc(strlen(argv[1])+strlen(release_s)+1);
	strcat(strcpy(release_name, argv[1]), release_s);

	if ((mkfifo(request_name, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("server failed to create request FIFO");
		return 1;
	}
	if ((mkfifo(release_name, FIFO_PERMS) == -1) && (errno != EEXIST)) {
		perror("server failed to create release FIFO");
		return 1;
	}

	while ( 1 ) {
		
	}

	return 0; 
}
