#ifndef ARGS_H
#define ARGS_H

#include <argp.h>

extern struct argp argp;

extern const char *argp_program_version;

struct arguments {
  char *global_sensitivity;
  char *movement_sensitivity;
  char *movement_acceleration;
  char *scroll_sensitivity;
  char *scroll_acceleration;
  char *scroll_deadzone;
  int verbose;
  int grab;
};

void parse_arguments(int argc, char **argv, struct arguments *arguments);

#endif // ARGS_H
