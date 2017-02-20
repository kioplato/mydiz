## Purpose: Makefile for the mydiz.

## Sets the compiler.
CC=gcc
## Sets the flags for the compiler.
CFLAGS=-Wall -g -c
## Sets the flags for the linker.
LDFLAGS=-g -o
## Sets the object files.
OBJ=obj/main.o obj/misc.o
## Sets the executable file.
EXE=mydiz

# Set the targets.

default: libraries

clean:
	rm -f $(EXE) $(OBJ);

## Set the dependencies.

libraries: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(EXE)

obj/main.o: ./src/main.c ./src/misc/misc.h
	$(CC) $(CFLAGS) ./src/main.c
	mv *.o obj/

obj/misc.o: ./src/misc/misc.h
	$(CC) $(CFLAGS) ./src/misc/misc.c
	mv *.o obj/
