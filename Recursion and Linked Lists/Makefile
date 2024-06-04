CC = gcc
CFLAGS = -ansi -pedantic -Wall
OBJ = lab5.o person.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

lab5: $(OBJ)
	$(CC) -o $@ $^

run: lab5
	./lab5

clean:
	rm -f $(OBJ) lab5

.PHONY: run clean
