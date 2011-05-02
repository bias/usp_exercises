#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	pid_t childpid = 0;
	int i, j, n, nchars;
	char *mybuf;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s num-processes num-chars\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);
	for (i = 1; i < n; i++)
		if (childpid = fork())
			break;

	nchars = atoi(argv[2]);
	mybuf = malloc(nchars+1);
	for (j = 0; j < nchars; j++)
		mybuf[j] = getchar();
	mybuf[nchars] = '\0';

	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld string:%s\n", i, (long)getpid(), (long)getppid(), (long)childpid, mybuf);
	return 0;
}
