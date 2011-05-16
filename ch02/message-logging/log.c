#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <emalloc.h>

#include <log.h>

#define TRAV_INIT_SIZE 8

typedef struct list_struct {
  data_t item;
  struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) {
  log_t *newnode;
  int nodesize;

  nodesize = sizeof(log_t) + strlen(data.string) + 1;
  if ( (newnode = (log_t *) emalloc(nodesize)) == NULL ) 
    return -1;
  newnode->item.time = data.time;
  newnode->item.string = (char *)newnode + sizeof(log_t);
  strcpy(newnode->item.string, data.string);
  newnode->next = NULL;
  if (headptr == NULL)
    headptr = newnode;
  else 
    tailptr->next = newnode;
  tailptr = newnode;
  return 0;
}

void clearlog(void) {
  log_t *travptr;
  while ( headptr->next != NULL ) {
    travptr = headptr;
    headptr = headptr->next;
    free(travptr);
  }
  free(headptr);
  headptr = NULL;
}

char *getlog(void) { 
  /* allocate space for string with entire log, return pointer to string */
  log_t *travptr;
  int strsize;
  char *wholelog;

  strsize = 0;
  travptr = headptr;
  while ( travptr != NULL ) {
    /* count char plus 1 bytes for newline */
    strsize += strlen( travptr->item.string ) + 1;
    travptr = travptr->next;
  }

  if ( (wholelog = (char *) emalloc(strsize + 1)) == NULL )
	  return NULL;
  travptr = headptr;
  while ( travptr != NULL ) {
    if ( travptr == headptr )
      strcat(strcpy(wholelog, travptr->item.string), "\n");
    else
      strcat(strcat(wholelog, travptr->item.string), "\n");
    travptr = travptr->next;
  }

  return wholelog;
}

int savelog(char *filename) {
  FILE *fp;
  char *log;

  fp = fopen(filename, "w");

  if ( fp == NULL ) {
    fprintf(stderr, "Can't open file!\n");
    return -1;
  } 
  else {
    log = getlog();
    fprintf(fp, "%s", log);
    free(log);
  }

  return 0;
}
