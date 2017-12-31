#include <stdlib.h>
#include <stdio.h> /* provides printf */
#include <dlfcn.h> /* provides dlopen and dlsym */

#include <getopt.h> /* provides getopt_long() */

void show_help_message() {
  printf("help message\n");
}

int main(int argc, char **argv) {

  void *plugin;
  int (*doSomething)();
  int rc;
  
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

  doSomething = dlsym(plugin,"doSomething");
  if (doSomething == NULL) {
    printf("Couldn't find doSomething() in %s: %s\n", arg_plugin, dlerror());
    exit (1);
  }

  rc = (*doSomething)();
  printf("%s's doSomething() returned %d\n", arg_plugin, rc);

}
