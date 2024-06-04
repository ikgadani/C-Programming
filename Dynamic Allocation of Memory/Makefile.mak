CC = gcc
CFLAGS = -ansi -pendantic -Wall
TARGET = a01

$(TARGET): $(TARGET).c
    $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

run $(TARGET)
    ,/$(TARGET)

clean:
    rm -f $(TARGET)