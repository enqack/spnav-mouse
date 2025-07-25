#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <spnav.h>

int uinput_fd = -1;

void cleanup(void) {
  spnav_close();
  if (uinput_fd > 0) {
    ioctl(uinput_fd, UI_DEV_DESTROY);
    close(uinput_fd);
  }
  printf("Clean exit. o7\n");
  exit(0);
}

void emit(int fd, int type, int code, int val) {
  struct input_event ie = {
    .type = type,
    .code = code,
    .value = val,
  };
  gettimeofday(&ie.time, NULL);
  if (write(fd, &ie, sizeof(ie)) != sizeof(ie)) {
    perror("Failed to write input event");
  }
}

void send_mouse_move(int x, int y) {
  if (x)
    emit(uinput_fd, EV_REL, REL_X, x);
  if (y)
    emit(uinput_fd, EV_REL, REL_Y, y);
  emit(uinput_fd, EV_SYN, SYN_REPORT, 0);
}

void send_scroll(int amount) {
  if (amount)
    emit(uinput_fd, EV_REL, REL_WHEEL, amount);
  emit(uinput_fd, EV_SYN, SYN_REPORT, 0);
}

void send_button(int code, int press) {
  emit(uinput_fd, EV_KEY, code, press);
  emit(uinput_fd, EV_SYN, SYN_REPORT, 0);
}

void setup_uinput() {
  struct uinput_setup usetup;

  uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (uinput_fd < 0) {
    perror("error: open /dev/uinput");
    exit(EXIT_FAILURE);
  }

  ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_LEFT);
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_RIGHT);

  ioctl(uinput_fd, UI_SET_EVBIT, EV_REL);
  ioctl(uinput_fd, UI_SET_RELBIT, REL_X);
  ioctl(uinput_fd, UI_SET_RELBIT, REL_Y);
  ioctl(uinput_fd, UI_SET_RELBIT, REL_WHEEL);

  ioctl(uinput_fd, UI_SET_EVBIT, EV_SYN);
  ioctl(uinput_fd, UI_SET_PROPBIT, INPUT_PROP_POINTER);

  memset(&usetup, 0, sizeof(usetup));
  usetup.id.bustype = BUS_USB;
  usetup.id.vendor  = 0x046d;
  usetup.id.product = 0xc077;
  strcpy(usetup.name, "Virtual Mouse");

  ioctl(uinput_fd, UI_SET_EVBIT, EV_ABS);
  ioctl(uinput_fd, UI_DEV_SETUP, &usetup);
  ioctl(uinput_fd, UI_DEV_CREATE);
}
