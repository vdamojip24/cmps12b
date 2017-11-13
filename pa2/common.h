#ifndef __HEADER_H__//preprocessor that isn't defined
#define __HEADER_H__//defines __HEADER_H__
# include <stdio.h>

#define SWAP(a, b, moves) { int temp = a; a = b; b = temp; moves += 3;}//swap method used throughout all the sorting algorithms that also increments the amount of moves by 3

void getAlgorithmName(char c, char **name);//declares the method that gets the specified algorithm
void printArray(int *array, int arrayLen, int numElements, int compares ,int moves,char algo);//declares the method that prints the particular statistics


#endif //ends the preprocessor conditional __HEADER_H__
