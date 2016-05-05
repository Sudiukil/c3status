CC=gcc
CFLAGS=-W -Wall -Wextra -Wconversion -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wuninitialized -Winit-self -Wundef -Wmissing-prototypes -Wstrict-prototypes -Wunreachable-code -Waggregate-return -Wswitch-default -Wswitch-enum
LDFLAGS=-Iinclude -lm -lasound -liw

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

EXEC=c3status
PREFIX=/usr

all: $(EXEC)

$(EXEC): $(OBJ) $(EXEC).c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ): config.h

config.h:
	cp config.example.h $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

manpage:
	make -C man

doc:
	make -C docs

clean:
	rm -f $(OBJ)
	rm -f $(EXEC)

install: $(EXEC) man/$(EXEC).1
	install -m 755 $(EXEC) $(DESTDIR)$(PREFIX)/bin/$(EXEC)
	install -m 644 man/$(EXEC).1 $(DESTDIR)$(PREFIX)/share/man/man1

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(EXEC)
