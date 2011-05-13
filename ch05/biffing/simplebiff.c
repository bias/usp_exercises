#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAILFILE "/private/var/mail/trevor"
#define SLEEPTIME 10

#define FOREVER 1

/* I'm skipping 5.32 - 5.35 since they are mostly mundane */
int main(int argc, char* argv[]) {
	struct stat statbuf;

	while( FOREVER ) {
		if ( stat(MAILFILE, &statbuf) != -1 && statbuf.st_size != 0 )
			fprintf(stderr, "%s", "\007");
		sleep(SLEEPTIME);
	}
}
