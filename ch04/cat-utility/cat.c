#include <stdlib.h> /* abort */
#include <stdio.h> /* BUFSIZE */
#include <fcntl.h> /* open */
#include <unistd.h> /* getopt */
#include <string.h> /* strcmp */

#include <custom.h> /* emalloc */

int main(int argc, char *argv[]) {
	char *buf;
	char c;
	int i, bufsiz, fd, bytesread, byteswritten;

	opterr = 0;
	bufsiz = BUFSIZ;
	byteswritten = 0;

	while ( (c = getopt(argc, argv, "u")) != -1 ) {
		switch (c) {
			case 'u':
				bufsiz = 1;
				break;
			case '?':
				fprintf(stderr, "Unknown option character -%c\n", optopt);
				return 1;
			default:
				abort();
		}
	}

	buf = emalloc(bufsiz);

	for (i = optind; i < argc; i++) {
		if ( !strcmp("-", argv[i]) )
			fd = 0;
		else
			fd = open(argv[i], O_RDONLY);
		while ( (bytesread = read(fd, buf, bufsiz)) > 0 && (byteswritten = write(1, buf, bytesread)) > 0 ) { }
		if ( bytesread == -1 )
			fprintf(stderr, "Couldn't read from %s\n", argv[i]);
		if ( byteswritten == -1 )
			fprintf(stderr, "Couldn't write to stdin\n");
		if ( fd != 0 )
			close(fd);
	}

	return 0;
}
