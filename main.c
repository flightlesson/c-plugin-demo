#include <stdlib.h>
#include <stdio.h> /* provides printf */
#include <dlfcn.h> /* provides dlopen and dlsym */

#include <getopt.h> /* provides getopt_long() */

#include "plugin.h"

void show_help_message() {
  printf("help message\n");
}

int main(int argc, char **argv) {

  void *plugin;
  void *(*plugin_create)();
  int (*plugin_doSomething)();
  void (*plugin_destroy)();
  void *pluginObj = 0;
  int rc;
  struct Stuff stuff;
  
  struct option options[] = {
    {"version", no_argument ,      NULL, 'V'},
    {"help",    no_argument ,      NULL, 'h'},
    {"plugin",  required_argument, NULL, 'p'},
    {"verbose", no_argument,       NULL, 'v'},
    {"quiet",   no_argument,       NULL, 'q'},
    { 0,        0,                 0,    0}
  };

  int arg_version = 0;
  int arg_help = 0;
  char *arg_plugin = NULL;
  int verbosity = 1;
  int error = 0;
  
  char c;
  while ((c=getopt_long(argc, argv, "p:hVvq", options, NULL)) >= 0) {
    printf("option %c\n", c);
    switch (c) {
    case 'V': arg_version = 1; break;
    case 'h': arg_help = 1; break;
    case 'p': arg_plugin = optarg; break;
    case 'q': --verbosity; break;
    case 'v': --verbosity; break;
    case '?': ++error; break;
    case ':': ++error; break;
    }
  }

  if (error) {
    /* getopt_long already showed the error message */
    show_help_message();
    exit (1);
  }

  if (arg_plugin == NULL) {
    printf("%s: --plugin <path-to-plugin> is required\n", argv[0]);
    show_help_message();
    exit (1);
  }
  
  if (arg_help) {
    show_help_message();
    exit (0);
  }

  plugin = dlopen(arg_plugin, RTLD_LAZY);
  if (plugin == NULL) {
    printf("Couldn't dlopen %s: %s\n", arg_plugin, dlerror());
    exit (1);
  }

  plugin_create = dlsym(plugin,"pluginCreate");
  if (plugin_create) {
    pluginObj = (*plugin_create)();
  }

  plugin_doSomething = dlsym(plugin,"pluginDoSomething");
  if (plugin_doSomething == NULL) {
    printf("Couldn't find pluginDoSomething() in %s: %s\n", arg_plugin, dlerror());
    exit (1);
  }

  stuff.i = 42;
  stuff.d = 3.14;
  stuff.name = "Stuff!";

  rc = (*plugin_doSomething)(pluginObj,&stuff);
  printf("%s's pluginDoSomething() returned %d\n", arg_plugin, rc);

  plugin_destroy = dlsym(plugin,"pluginDestroy");
  if (plugin_destroy) {
    (*plugin_destroy)(pluginObj);
  }

}

