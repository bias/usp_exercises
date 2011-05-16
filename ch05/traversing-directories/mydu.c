#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#include <emalloc.h>

/* I'm skipping the breadth first apply */
int depthfirstapply(char *path, int pathfun(char *pathl));
int sizepathfun(char *path);

int main(int argc, char *argv[]) { 

	if (argc != 2 ) {
		fprintf(stderr, "Usage: %s rootpath\n", argv[0]);
		return 1;
	}

	depthfirstapply(argv[1], sizepathfun);

	return 0; 
}

int depthfirstapply(char *path, int pathfun(char *pathl)) {
	/* XXX will use a fixed sized buf here and not size check */ 
	char buf[1024];
	struct stat statbuf;
	struct dirent *direntp;
	DIR *dirp;
	int sum = 0;

	if ((dirp = opendir(path)) == NULL) {
		perror("Can't open directory");
		return -1;
	}

	while ((direntp = readdir(dirp)) != NULL) {

		if ( strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 ) {
			strcat(strcat(strcpy(buf, path), "/"), direntp->d_name);

			if ( lstat(buf, &statbuf) == -1) {
				perror("Couldn't get file status");
				fprintf(stderr, "\t%s %s\n", path, direntp->d_name);
				return -1;
			}

			if ( S_ISDIR(statbuf.st_mode) ) {
				sum += pathfun(buf);	
				depthfirstapply(buf, pathfun);
			}
			else
				sum += pathfun(buf);	
		}

	}

	while ((closedir(dirp) == -1) && (errno == EINTR)) {}

	/*stat(path, &statbuf);*/
	printf("%i %s\n", sum, path);

	return 1;	
}

int sizepathfun(char *path) {
	struct stat statbuf;

	if ( lstat(path, &statbuf) == -1) {
		perror("Couldn't get file status");
		fprintf(stderr, "\t%s\n", path);
		return -1;
	}
	/* printing off_t */
	/* printf("%li\t%s\n", (long)statbuf.st_size, path); */

	return statbuf.st_size;
}
