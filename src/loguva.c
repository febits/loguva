#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <color.h>

void loguva_test() {
  struct style s = {BRIGHT_GREEN, DEFAULT(BG), BOLD | ITALIC};
  printfc(&s, "Hello!\n");
}
