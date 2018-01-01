#include <stdlib.h>
#include <stdio.h>

#include "plugin.h"

int pluginDoSomething(void *thisObj, Stuff *stuff) {
  printf("C did something; stuff is %s\n",stuff->name);
  return 0;
}
