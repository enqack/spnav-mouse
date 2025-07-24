# Makefile for spnav_mouse

TARGET     := spnav-mouse
SRC        := spnav-mouse.c
OBJ        := $(SRC:.c=.o)
CC         := gcc
CFLAGS     := -Wall -Wextra -O2
LDFLAGS    := -lspnav -lm
PREFIX     := /usr/local
BINDIR     := $(PREFIX)/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

