OBJS 	= main.o blocktest.o metadata_functions.o
SOURCE	= main.c blocktest.c metadata_functions.c
HEADER  = file_structure.h metadata_functions.h
OUT  	= mydiz
CC		= gcc
FLAGS   = -g -c  

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

blocktest.o: blocktest.c
	$(CC) $(FLAGS) blocktest.c

metadata_functions.o: metadata_functions.c
	$(CC) $(FLAGS) metadata_functions.c

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
