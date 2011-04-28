#include <stdio.h>
#include <stdlib.h>
#include <custom.h>

void* emalloc(size_t size) {
  void *p;
  if ( (p = malloc(size)) == NULL ) {
    fprintf(stderr, "Bad malloc at %s: %i\n", __FILE__, __LINE__);
    exit(OOM);
  }
  return p;
}
