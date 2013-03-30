#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* I also cut this one short to get a move on things */

int plain_stty();
int line_stty();
int all_stty();

int main(int argc, char *argv[]) { 

	if ( argc == 1 ) {
		plain_stty();
	}
	else if ( argc == 2 ) {
		if ( strcmp(argv[1], "-g") == 0 ) {
			line_stty();
		}
		if ( strcmp(argv[1], "-a") == 0 ) {
			all_stty();
		}
	}

	return 0; 
}

/* I simply replicated the output of stty */
/* stty handels the absense of some flags differently so this is surely wrong */
/* also, there was a descrepency for the oflags, and I ommited some flags that weren't on */
int plain_stty() {
	struct termios term;

	if ( tcgetattr(STDIN_FILENO, &term) == -1 )
		return -1;
	
	printf("speed %lu baud;\n", term.c_ispeed);

	printf("lflags: %s%s%s%s\n",
		(term.c_lflag & ECHOE) == ECHOE ? "echoe " : "",
		(term.c_lflag & ECHOKE) == ECHOKE ? "echoke " : "",
		(term.c_lflag & ECHOCTL) == ECHOCTL ? "echoctl " : "",
		(term.c_lflag & PENDIN) == PENDIN ? "pendin" : "");

	printf("iflags: %s\n",
		(term.c_iflag & IUTF8) == IUTF8 ? "iutf8" : "");

	printf("oflags: %s%s\n", 
	/*
		((term.c_oflag & OPOST) == OPOST) ? "post " : "", 
		((term.c_oflag & ONLCR) == ONLCR) ? "onclr " : "",
		*/
		((term.c_oflag & OXTABS) == OXTABS) ? "oxtabs " : "-oxtabs ",
		((term.c_oflag & ONOEOT) == ONOEOT) ? "onoeot " : "" );

	printf("cflags: %s%s\n",
		((term.c_cflag & CS7) == CS7) ? "cs7 " : "",
		((term.c_cflag & PARENB) == PARENB) ? "parenb " : "-parenb ");
	
	return 0;
}

int line_stty() {
	struct termios term;

	if ( tcgetattr(STDIN_FILENO, &term) == -1 )
		return -1;
	
	printf("fixme: flags don't work yet\n");
	
	return 0;
}

int all_stty() {
	struct termios term;

	if ( tcgetattr(STDIN_FILENO, &term) == -1 )
		return -1;
	
	printf("fixme: flags don't work yet\n");
	
	return 0;
}
