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

  if (spnav_open() == -1) {
    fprintf(stderr, "failed to connect to spacenavd\n");
    return 1;
  }

  setup_uinput();
  spnav_cfg_set_grab(args.grab);
  spnav_cfg_set_sens(atof(args.global_sensitivity));

  float sens_array[6] = {
    atof(args.movement_sensitivity),
    atof(args.movement_sensitivity),
    atof(args.movement_sensitivity),
    1.0,
    atof(args.scroll_sensitivity),
    1.0
  };

  spnav_cfg_set_axis_sens(sens_array);
  spnav_cfg_set_deadzone(4, atoi(args.scroll_deadzone));

  spnav_event sev;
  while (1) {
    if (spnav_wait_event(&sev) <= 0)
      continue;

    process_spnav_events(&args);
    spnav_remove_events(SPNAV_EVENT_MOTION);
  }
}
