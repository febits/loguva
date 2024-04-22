#include <stdio.h>
#include <stdlib.h>

#include "loguva.h"

int main(void) {

  loguva_add_stream(stdout);
  loguva_add_file("/tmp/loguva.log");
  loguva_add_file("/tmp/a.log");

  loguva(DEBUG, "value of var (x): 15");
  loguva(INFO, "listening on port: 12000");
  loguva(WARNING, "possible memory leak");
  loguva(ERROR, "out of bound");
  loguva(FATAL, "received SIGINT");

  return EXIT_SUCCESS;
}
