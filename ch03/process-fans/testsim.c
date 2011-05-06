#include <stdio.h>

int main(int argc, char *argv[]) {
	int n, m;	
	n = atoi(argv[1]);
	for ( m = atoi(argv[2]); m > 0; m--) {
		sleep(n);
		fprintf(stderr, "pid: %ld\n", (long)getpid());
	}
	return 0;
}
