#include <stdio.h>
#include <string.h>
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

	/* break on EOF or error */
	while ( fgets(buf, MAX_CANON, stdin) != NULL ) {

		if ( pr_count == pr_limit )
			wait(NULL);

		switch ( fork() ) {

			case -1:
				perror("Failed to fork");
				return 1;

			case  0:
				/* XXX remove trailing newline */
				buf[strlen(buf)-1] = '\0';
				if ( makeargv(buf, delim, &pr_argv) == -1 )
					perror("Couldn't construct argument array");
				execvp(pr_argv[0], pr_argv);
				perror("Child failed to exec");
				return 1;

			default:
				++pr_count;
				/* Check for any (-1) finished children */
				switch ( waitpid(-1, NULL, WNOHANG) ) {
					case -1:
						perror("Failed to wait");
						return 1;
					case  0:
						/* unfinished children */
						break;
					default:
						--pr_count;
						break;
				}
				break;
		}
	}
	
	if ( ferror(stdin) ) {
		perror("Error reading from stdin"); 
		return ferror(stdin);
	}

	wait(NULL);

	return 0;
}
