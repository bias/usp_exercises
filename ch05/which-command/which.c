#include <stdlib.h> /* getenv */
#include <stdio.h> /* fprintf */
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include <makeargv.h>

int tokenize_path(char ***);
int search_dir(char *, char *);
/* int checkexecutable(char *); */

int main(int argc, char *argv[]) {
	int i, j;
	int pathc;
	char *name;
	char **pathv;


	if ( (pathc = tokenize_path(&pathv)) < 0 )
		fprintf(stderr, "Can't tokenize path\n");

	for (j=1; j<argc; j++) {
		/* XXX for now, presume no flags */
		name = argv[j];
		for (i=0; i<pathc; i++) {
			if (search_dir(pathv[i], name) == 0) {
				printf("%s/%s\n", pathv[i], name);
				break;
			}
		}
	}

	return 0;
}

int tokenize_path(char ***pathv) {
	char *env_path;
	char delim[] = ":";

	if ( (env_path = getenv("PATH")) == NULL ) {
		perror("Can't get env");
		return -1;
	}
	return makeargv(env_path, delim, pathv);
}

int search_dir(char *path, char *name) {
	struct dirent *direntp;
	DIR *dirp;

	if ((dirp = opendir(path)) == NULL) {
		perror("Can't open directory");
		return errno;
	}

	while ((direntp = readdir(dirp)) != NULL) {
		if (strcmp(direntp->d_name, name) == 0) 
			return 0;
	}

	while ((closedir(dirp) == -1) && (errno == EINTR)) {}

	return 1;	
}

/* I'm gonna skip this part since my which doesn't check executabilty
int checkexecutable(char *name) {
	return 0;
}
*/
