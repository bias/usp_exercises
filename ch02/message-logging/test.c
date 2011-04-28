#include "log.h"

#include "stdlib.h" /* malloc */

int main() { 
 
  data_t logs;
  char msg1[] = "test1"; 
  char msg2[] = "test2"; 
  char msg3[] = "test3"; 
  char *log;
  char logname1[] = "test_3.log";
  char logname2[] = "test_0.log";

  if (time(&(logs.time)) == -1) 
    return -1;

  logs.string = msg1;
  addmsg(logs);
  logs.string = msg2;
  addmsg(logs);
  logs.string = msg3;
  addmsg(logs);

  log = getlog();
  savelog(logname1); 

  clearlog();
  log = getlog();
  savelog(logname2); 

  return 0;
}
