#include "log.h"

data_t log_;

int main() { 
 
  if (time(&(log_.time)) == -1) 
    return -1;
  addmsg(log_);
  
}
