# MAKEFILE

CC = gcc
CFLAGS = -g
OBJFILES = mizzo.o 
TARGET = mizzo

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)