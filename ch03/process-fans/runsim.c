#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <limits.h>

#include <custom.h>

int main (int argc, char *argv[]) {
	char buf[MAX_CANON], delim[] = " \t";
	char **pr_argv;
	int pr_limit, pr_count = 0;

	if (argc != 2) { 
		fprintf(stderr, "Usage: %s process_limit\n", argv[0]);
		return 1;
	}
	pr_limit = atoi(argv[1]);

	while ( !feof(stdin) ) {
		if ( pr_count == pr_limit )
			wait(NULL);
		if ( fgets(buf, MAX_CANON, stdin) == NULL && ferror(stdin) ) {
			perror("Error reading from stdin"); 
			return ferror(stdin);
		}
		switch ( fork() ) {
			case -1:
				perror("Failed to fork");
				return 1;
			case  0:
				if ( makeargv(buf, delim, &pr_argv) == -1 )
					perror("Couldn't construct argument array");
				execvp(pr_argv[0], &pr_argv[0]);
				perror("Child failed to exec");
		}
	}

	return 0;
}
