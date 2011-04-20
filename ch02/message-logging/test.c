#include "log.h"

#include "stdlib.h" /* malloc */

int main() { 
 
  data_t logs;
  char msg[5] = "test"; 
  char *log;
  char logname1[11] = "test_3.log";
  char logname2[11] = "test_0.log";

  if (time(&(logs.time)) == -1) 
    return -1;
  logs.string = msg;

  addmsg(logs);
  addmsg(logs);
  addmsg(logs);
  
  log = getlog();
  savelog(logname1); 

  clearlog();
  
  log = getlog();
  savelog(logname2); 

  return 0;
}
