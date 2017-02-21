## Purpose: Makefile for the mydiz.

## Sets the compiler.
CC=gcc
## Sets the flags for the compiler.
CFLAGS=-std=c11 -Wall -g -c
## Sets the flags for the linker.
LDFLAGS=-std=c11 -g -o
## Sets the object files.
OBJ=obj/main.o obj/misc.o obj/metadata_functions.o obj/dinode_list.o obj/operations.o
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

obj/metadata_functions.o: ./src/metadata/metadata_functions.c
	$(CC) $(CFLAGS) ./src/metadata/metadata_functions.c
	mv *.o obj/

obj/dinode_list.o: ./src/dinode_list/dinode_list.c ./src/dinode_list/dinode_list.h
	$(CC) $(CFLAGS) ./src/dinode_list/dinode_list.c
	mv *.o obj/

obj/operations.o: ./src/operations/operations.c
	$(CC) $(CFLAGS) ./src/operations/operations.c
	mv *.o obj/
