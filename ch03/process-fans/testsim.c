#include <stdio.h> /* fprintf */
#include <stdlib.h> /* atoi */
#include <unistd.h> /* sleep */

int main(int argc, char *argv[]) {
	int n, m;	

	if ( argc != 3 ) {
		fprintf(stderr, "Usage %s sleep_time num_loops\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	for ( m = atoi(argv[2]); m > 0; m--) {
		sleep(n);
		fprintf(stderr, "pid: %ld\n", (long)getpid());
	}

	return 0;
}
