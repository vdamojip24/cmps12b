CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
CC = gcc 

sorting: minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o common.o sorting.o
	$(CC) -o sorting minsort.o bubblesort.o insertionsort.o quicksort.o common.o mergesort.o sorting.c

.PHONY: all
all: sorting

minsort.o: minsort.c
	$(CC)	$(CFLAGS)	-o minsort.o -c minsort.c

bubblesort.o:bubblesort.c	
	$(CC)	$(CFLAGS)	-o bubblesort.o -c bubblesort.c

insertionsort.o:insertionsort.c	
	$(CC)	$(CFLAGS)	-o insertionsort.o -c insertionsort.c

quicksort.o:quicksort.c	
	$(CC)	$(CFLAGS)	-o quicksort.o -c quicksort.c

mergesort.o:mergesort.c	
	$(CC)	$(CFLAGS)	-o mergesort.o -c mergesort.c

common.o:common.c	
	$(CC)	$(CFLAGS)	-o common.o -c common.c

clean:
	rm -rf *.o sorting
