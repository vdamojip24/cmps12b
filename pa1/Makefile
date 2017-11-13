CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
CC = gcc $(CFLAGS)


OBJ = parfait.o bv.o sieve.o

all: $(OBJ)
	$(CC)	-o parfait $(OBJ) -lm

clean:
	rm -f $(OBJ) parfait  


