#include "args.h"
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "Version: 0.5";

static char doc[] = "SpaceMouse to mouse control bridge.";

static struct argp_option options[] = {
  {"global-sensitivity",    's', "SENSITIVITY", 0, "Set global sensitivity",           0 },
  {"movement-sensitivity",  'm', "SENSITIVITY", 0, "Set movement sensitivity",         0 },
  {"movement-acceleration", 'a', "FACTOR",      0, "Set movement acceleration factor", 0 },
  {"scroll-sensitivity",    'r', "SENSITIVITY", 0, "Set scroll sensitivity",           1 },
  {"scroll-acceleration",   'o', "FACTOR",      0, "Set scroll acceleration factor",   1 },
  {"scroll-deadzone",       'd', "DEADZONE",    0, "Set scroll deadzone",              1 },
  {"verbose",               'v', 0,             0, "Produce verbose output",           2 },
  {"grab",                  'g', 0,             0, "Exclusively grab SpaceMouse",      2 },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case 's': arguments->global_sensitivity = arg; break;
    case 'm': arguments->movement_sensitivity = arg; break;
    case 'a': arguments->movement_acceleration = arg; break;
    case 'r': arguments->scroll_sensitivity = arg; break;
    case 'o': arguments->scroll_acceleration = arg; break;
    case 'd': arguments->scroll_deadzone = arg; break;
    case 'g': arguments->grab = 1; break;
    case 'v': arguments->verbose = 1; break;
    default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0};

void parse_arguments(int argc, char **argv, struct arguments *arguments) {
  arguments->grab = 0;
  arguments->verbose = 0;
  arguments->global_sensitivity = "0.5";
  arguments->movement_sensitivity = "0.10";
  arguments->movement_acceleration = "0.5";
  arguments->scroll_deadzone = "2";
  arguments->scroll_sensitivity = "0.025";
  arguments->scroll_acceleration = "0.125";

  argp_parse(&argp, argc, argv, 0, 0, arguments);
}
