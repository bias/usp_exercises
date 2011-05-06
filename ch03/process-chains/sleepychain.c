#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0;
	int i, n, k, m;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s num-processes num-prints sleep\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	for (i = 1; i < n; i++)
		if ( (childpid = fork()) )
			break;

	m = atoi(argv[3]);
	sleep(m);
	for (k = atoi(argv[2]); k > 0; k--)
		fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
	return 0;
}
