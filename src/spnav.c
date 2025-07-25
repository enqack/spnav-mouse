#include "spnav.h"
#include "input.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void setup_spnav(struct arguments *args) {
  if (spnav_open() == -1) {
    fprintf(stderr, "failed to connect to spacenavd\n");
    exit(1);
  }

  spnav_cfg_set_grab(args->grab);
  spnav_cfg_set_sens(atof(args->global_sensitivity));

  float sens_array[6];
  sens_array[0] = atof(args->movement_sensitivity);
  sens_array[1] = atof(args->movement_sensitivity);
  sens_array[2] = atof(args->movement_sensitivity);
  sens_array[3] = 1.0;
  sens_array[4] = atof(args->scroll_sensitivity);
  sens_array[5] = 1.0;
  spnav_cfg_set_axis_sens(sens_array);

  spnav_cfg_set_deadzone(4, atoi(args->scroll_deadzone));
}

void process_spnav_events(struct arguments *args) {
  spnav_event sev;
  while (1) {
    if (spnav_wait_event(&sev) <= 0)
      continue;

    if (sev.type == SPNAV_EVENT_MOTION) {
      int tx = apply_acceleration(sev.motion.x, atof(args->movement_acceleration));
      int tz = apply_acceleration(-sev.motion.z, atof(args->movement_acceleration));
      int scroll = apply_acceleration(sev.motion.ry, atof(args->scroll_acceleration));

      if (tx || tz) {
        if (args->verbose)
          printf("MOVE: tx=%d tz=%d\n", tx, tz);
        send_mouse_move(tx, tz);
      }

      if (scroll) {
        if (args->verbose)
          printf("SCROLL: scroll=%d\n", scroll);
        send_scroll(scroll);
      }

    } else if (sev.type == SPNAV_EVENT_BUTTON) {
      if (sev.button.bnum == 0) {
        send_button(BTN_LEFT, sev.button.press);
      } else if (sev.button.bnum == 1) {
        send_button(BTN_RIGHT, sev.button.press);
      }
    }

    spnav_remove_events(SPNAV_EVENT_MOTION);
  }
}
