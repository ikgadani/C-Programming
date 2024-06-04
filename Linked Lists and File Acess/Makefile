
CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
OBJS = a02.o students.o

all: main

a02: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: main
	./main students.dat

clean:
	rm -f main $(OBJS)

.PHONY: all run clean