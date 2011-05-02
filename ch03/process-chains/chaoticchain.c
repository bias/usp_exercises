#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0;
	int i, n;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s num-processes\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	for (i = 1; i < n; i++)
		if (childpid = fork())
			break;

	fprintf(stderr, "i:%d ", i); 
	fprintf(stderr, "process ID:%ld ", (long)getpid()); 
	fprintf(stderr, "parent ID:%ld ", (long)getppid()); 
	fprintf(stderr, "child ID:%ld\n", (long)childpid); 
	return 0;
}
