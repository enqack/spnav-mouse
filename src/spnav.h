#ifndef SPNAV_H
#define SPNAV_H

#include <spnav.h>
#include "args.h"

// Initialize and configure SpaceNav with provided args
void setup_spnav(struct arguments *args);

// Handle SpaceNav events and forward them to uinput
void process_spnav_events(struct arguments *args);

#endif // SPNAV_H
