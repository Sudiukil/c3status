CC=gcc
CFLAGS=-W -Wall -Wwrite-strings -Wfloat-equal
LDFLAGS=-Iinclude -lm -lasound -liw

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

PREFIX=/usr

all: c3status

c3status: $(OBJ) c3status.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ): config.h

config.h:
	cp config.example.h $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm src/*.o

mrproper: clean
	rm c3status

install: c3status
	install -m 755 c3status $(DESTDIR)$(PREFIX)/bin/c3status

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/c3status
