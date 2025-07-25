TARGET     := spnav-mouse
CC         := gcc
CFLAGS     := -Wall -Wextra -O2 -std=gnu99
LDFLAGS    := -lspnav -lm
PREFIX     := /usr/local
BINDIR     := $(PREFIX)/bin

SRC_DIR    := src
SRC        := $(SRC_DIR)/main.c \
		      $(SRC_DIR)/args.c \
              $(SRC_DIR)/input.c \
              $(SRC_DIR)/util.c \
              $(SRC_DIR)/spnav.c

OBJ        := $(SRC:.c=.o)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
