#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include <emalloc.h> /* emalloc */

#define FOREVER 1

time_t lastmod(char *);
char *convertnews(char *);

/* I'm skipping the config file, to get a move on things */

int main(int argc, char* argv[]) {
	time_t mtime, ttime; 
	char *newsfile;
	int sleeptime;

	if (argc != 3)
		fprintf(stderr, "Usage: %s newsgroup sleeptime\n", argv[0]);

	newsfile = convertnews(argv[1]);
	sleeptime = atoi(argv[2]);

	if ((mtime = lastmod(newsfile)) == -1) {
		fprintf(stderr, "Couldn't access newsgroup file\n");
		return 1;
	}
	printf("%s last updated %s", argv[1], ctime(&mtime)); /* ctime appends \n */
	
	while ( FOREVER ) {
		sleep(sleeptime);
		if ((ttime = lastmod(newsfile)) == -1) {
			fprintf(stderr, "Couldn't access newsgroup file: %s\n", newsfile);
			return 1;
		}
		if ( difftime(ttime,  mtime) > 0 ) {
			mtime = ttime;
			printf("%s updated %s", argv[1], ctime(&mtime));
		} 
	}
	return 0;
}

time_t lastmod(char *pathname) {
	struct stat statbuf;

	if ( stat(pathname, &statbuf) == -1) {
		perror("Couldn't get file status");
		return -1;
	}

	return statbuf.st_mtime; 
}

char *convertnews(char *newsgroup) {
	char defaultdir[] = "/var/spool/news/";
	char *newsdir;
	char *newspath;

	if ((newsdir = getenv("NEWSDIR")) == NULL) {
		newsdir = defaultdir;
	}

	newspath = emalloc(strlen(newsdir)+strlen(newsgroup)+1);
	return strcat(strcpy(newspath, newsdir), newsgroup);
}
