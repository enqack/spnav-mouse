#ifndef UINPUT_H
#define UINPUT_H

#include <linux/uinput.h>

void setup_uinput();
void emit(int fd, int type, int code, int val);
void send_mouse_move(int x, int y);
void send_scroll(int amount);
void send_button(int code, int press);
void cleanup(int sig);

extern int uinput_fd;

#endif // UINPUT_H
