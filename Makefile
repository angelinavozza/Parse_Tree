CC = gcc
CFLAGS = -g -Wall
OBJFLAGS = -g -Wall -c
TARGETS = tree main

all: $(TARGETS)

tree: tree.c tree.h
	$(CC) $(OBJFLAGS) $@.c
main: tree.o main.c
	$(CC) $(CFLAGS) $@.c tree.o -o $@
	./$@

clean:
		rm *.o main
		rm -r *.dSYM