CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -Wpedantic -std=c99 -g
OBJECT1 =	encode.o huffman.o stack.o
OBJECT2	=	decode.o huffman.o stack.o
.PHONY: all
all:	encode	decode

encode:	$(OBJECT1)
	$(CC) $(CFLAGS) $(OBJECT1) -o encode

decode:	$(OBJECT2)
	$(CC) $(CFLAGS) $(OBJECT2) -o decode

encode.o : encode.c
		$(CC)	$(CFLAGS) -c encode.c
decode.o : decode.c
		$(CC)	$(CFLAGS) -c decode.c

huffman.o : huffman.c
		$(CC)	$(CFLAGS) -c huffman.c
		
stack.o : stack.c
		$(CC)	$(CFLAGS) -c stack.c

.PHONY: clean
clean:
		rm -f decode decode.o encode encode.o huffman.o stack.o
