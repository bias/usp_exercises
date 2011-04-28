#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <custom.h>

/* utility functions */
void print_env();
int split_assign(char*, char*, char*);

void replace_environ(char**);
void append_environ(char**);

extern char **environ;

/* command [-i] [name=value ...] [utility [argument ...]] */

int main(int argc, char *argv[]) {

	if (argc == 1) {
		print_env();
	}
	else if ( strcmp(argv[1], "-i") == 0 ) {
		replace_environ(argv);
	}
	else {
		append_environ(argv);
	}

	return 0;
}


void print_env() {
	int i;
	for (i=0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}

int split_assign(char *s, char *var, char *val) {

	while ( *s != '=' && (*var = *s) != '\0' ) { 
		s++; 
		var++; 
	}
	if ( *var |= '\0' )
		*var = '\0';

	if (*s != '=')
		return -1;

	s++;

	while ( (*val = *s) != '\0' ) { 
		s++; 
		val++; 
	}
	if ( *val |= '\0' )
		*val = '\0';

	return 0;
}

void replace_environ(char** argv) {

	int i;
	int offset;

	char **tailp;
	char **headp;
	char **utilp;
	char **environ_new;
	char *util;
	char var_s[250], value_s[250];

	/* Offset pointers by "command [-i]" */
	offset = 2;
	tailp = argv + offset; 
	headp = argv + offset; 

	/* Grab pointer to the beginning of utility */
	while ( *tailp != NULL && split_assign(*tailp, var_s, value_s) == 0 )
		tailp++;

	utilp = tailp;

	/* Grab pointer to actual tail of args */
	while (*tailp != NULL )
		tailp++;

	/* Allocate memory for new environ */
	/* XXX we don't check for duplicate vars */
	environ_new = emalloc( sizeof(utilp - headp) );
	for (i=0; i< utilp - headp; i++) {
		environ_new[i] = emalloc( sizeof(argv[i+offset]) );
		environ_new[i] = argv[i+offset];
	}
	environ = environ_new;

			
	/* If utility was specified, concat it with args and run it */
	/* Otherwise, print env */
	if (utilp != NULL) {
		util = emalloc( sizeof(tailp - utilp) + sizeof(char) * (tailp-utilp) );
		while ( *utilp != NULL ) {
			strcat(util, *utilp);
			strcat(util, " ");
			utilp++;
		}
		system(util);
	}
	else
		print_env();
}

void append_environ(char** argv) {

	int offset;

	char **tailp;
	char **headp;
	char **utilp;
	char *util;
	char var_s[250], value_s[250];

	/* Offset pointers by "command" */
	offset = 1;
	tailp = argv + offset; 
	headp = argv + offset;

	/* Grab pointer to the beginning of utility */
	while ( *tailp != NULL && split_assign(*tailp, var_s, value_s) == 0 ) {
		/* they wanted me to check with getenv and overwrite */
		/* but this works better */
		setenv(var_s, value_s, 1);
		tailp++;
	}

	utilp = tailp;

	/* Grab pointer to actual tail of args */
	while (*tailp != NULL )
		tailp++;
	
	/* If utility was specified, concat it with args and run it */
	/* Otherwise, print env */
	if (utilp != NULL) {
		util = emalloc( sizeof(tailp - utilp) + sizeof(char) * (tailp-utilp) );
		while ( *utilp != NULL ) {
			strcat(util, *utilp);
			strcat(util, " ");
			utilp++;
		}
		system(util);
	}
	else
		print_env();
}
