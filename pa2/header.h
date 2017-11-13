#ifndef __HEADER_H__//preprocessor that isn't defined yet
#define __HEADER_H__// defines the preprocessor __HEADER_H__

# include <stdio.h>

#define SWAP(a, b, moves) { int temp = a; a = b; b = temp; moves += 3;}//swap method that swaps two variables and also increments the number of moves by 3

void printArray(int *array, int arrayLen, int numElements, int compares ,int moves);//declares the method that prints out all the statistics


#endif //ends the preprocessor conditional __HEADER_H__ 
