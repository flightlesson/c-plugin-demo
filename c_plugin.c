#include <stdlib.h>
#include <stdio.h>

#include "plugin.h"

int pluginDoSomething(void *thisObj) {
  printf("C did something\n");
  return 0;
}
