#include <stdlib.h>
#include <signal.h>
#include <argp.h>
#include "args.h"
#include "input.h"
#include "spnav.h"

int main(int argc, char **argv) {
  signal(SIGINT, cleanup);

  struct arguments args = {
    .grab = 0,
    .verbose = 0,
    .global_sensitivity = "0.5",
    .movement_sensitivity = "0.10",
    .movement_acceleration = "0.5",
    .scroll_deadzone = "2",
    .scroll_sensitivity = "0.025",
    .scroll_acceleration = "0.125"
  };

  argp_parse(&argp, argc, argv, 0, 0, &args);

  setup_spnav(&args);
  setup_uinput();

  process_spnav_events(&args);

  return 0;
}
