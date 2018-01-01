#include "plugin.h"
#include "Klass.hpp"

void *pluginCreate() { 
  return new Klass();
}
int pluginDoSomething(void *thisKlass, Stuff *stuff) {
  return static_cast<Klass *>(thisKlass)->doSomething(stuff);
}


void pluginDestroy(void *thisKlass) {
  delete static_cast<Klass *>(thisKlass);
}
