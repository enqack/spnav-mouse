#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <signal.h>
#include <argp.h>
#include <spnav.h>

static char doc[] = "SpaceMouse to mouse control bridge.";
const char *argp_program_version = "Version: 0.5";

static struct argp_option options[] = {
  {"verbose", 'v', 0, 0, "Produce verbose output" },
  {"grab",    'g', 0, 0, "Exclusively grab SpaceMouse" },
  { 0 }
};

struct arguments
{
  int verbose, grab;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'g':
      arguments->grab = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

int uinput_fd;

void cleanup(int sig) {
	if (uinput_fd > 0) {
		ioctl(uinput_fd, UI_DEV_DESTROY);
		close(uinput_fd);
	}
	spnav_close();
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
  (void)write(fd, &ie, sizeof(ie));
}

void send_mouse_move(int dx, int dy) {
	if (dx)
		emit(uinput_fd, EV_REL, REL_X, dx);
	if (dy)
		emit(uinput_fd, EV_REL, REL_Y, dy);
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

  // Set capabilities
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

int main(int argc, char **argv) {
	signal(SIGINT, cleanup);

  struct arguments arguments;

	arguments.grab = 0;
	arguments.verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

	if (spnav_open() == -1) {
		fprintf(stderr, "failed to connect to spacenavd\n");
		return 1;
	}

	setup_uinput();

	spnav_event sev;
	const int motion_scale = 10;
	const int scroll_scale = 50
	;

	while (1) {
		if (spnav_wait_event(&sev) <= 0)
			continue;

		if (sev.type == SPNAV_EVENT_MOTION) {
      int dx = sev.motion.x / motion_scale;
			int dz = -sev.motion.z / motion_scale;
			int dy = sev.motion.y / scroll_scale;

			if (dx || dz)
				if (arguments.verbose)
        	printf("MOVE: dx=%d zy=%d\n", dx, dz);
				send_mouse_move(dx, dz);
			if (dy)
				if (arguments.verbose)
					printf("SCROLL: dy=%d\n", dy);
				send_scroll(dy);

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

