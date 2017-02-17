OBJS 	= main.o blocktest.o
SOURCE	= main.c blocktest.c
HEADER  = block.h
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

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
