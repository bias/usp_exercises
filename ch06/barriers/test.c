#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <barrier.h>

int main (int argc, char *argv[]) {
  pid_t childpid = 0; 
  int i, n;

  if (argc != 3){   /* check for valid number of command-line arguments */ 
    fprintf(stderr, "Usage: %s barrier processes \n", argv[0]);
    return 1; 
  }     

  n = atoi(argv[2]);  

  for (i = 1; i < n; i++)
    if ( (childpid = fork()) )
      break;
  
  waitatbarrier(argv[1]);
  fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

  waitatbarrier(argv[1]);
  fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

  return 0; 
}
