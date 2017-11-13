CC = gcc
CFLAGS := -Wall -Wextra -Werror -pedantic  -g
#CFLAGS := -g
CFLAGS2 = flex

.PHONY: all
all: banhammer 

banhammer : bf.h ll.o hash.o main.o aes.o
	$(CC) $(CFLAGS) -o banhammer  ll.o hash.o main.o aes.o 

main.o : main.c
	$(CC) $(CFLAGS) -o main.o  -c main.c

ll.o : ll.c ll.h
	$(CC) $(CFLAGS) -o ll.o  -c ll.c

hash.o : hash.c hash.h 
	$(CC) $(CFLAGS) -o hash.o -c hash.c 

aes.o : aes.h aes.c
	$(CC) $(CFLAGS) -o aes.o -c  aes.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: words.I
	$(CFLAGS2) words.I
	
	
	

.PHONY : clean	

clean:
	rm -rf *.o \
	rm banhammer
