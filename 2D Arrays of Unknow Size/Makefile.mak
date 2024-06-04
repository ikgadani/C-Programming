# Compiler and flags
CC = gcc


# Default target
all: lab3

# Compile the program
lab3: lab3.c
    $(CC) -o lab3 lab3.c

# Run the program
run: lab3
    ./lab3

# Clean up object files and executable
clean:
    rm -f lab3
