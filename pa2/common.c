# include <stdio.h>
# include "common.h"//header file for common.c

char *algoName[] = {"Bubble", "Insertion", "Min", "Quick", "Merge"};//the names of the sorting types

void getAlgorithmName(char c, char **name)//takes in the name of the sorting type and the pointer to it
{
    //char *algoName[] = {"Bubble", "Insertion", "Min", "Quick", "Merge"};
    *name = NULL;
 
    switch (c)//allows you to type in a letter for a specified algorithm
    {
        case 'b':
            *name = algoName[0];
        break;
            
        case 'i':
            *name = algoName[1];
        break;

        case 'm':
            *name = algoName[2];
        break;

        case 'q':
            *name = algoName[3];
        break;

        case 'M':
            *name = algoName[4];
        break;

        default:
            printf("Error. Unknown algorithm\n");

    }

}


void printArray(int *array, int arrayLen, int numElements, int compares ,int moves, char algo)
{
    int elementsToPrint = numElements < arrayLen ? numElements : arrayLen;// if else that either prints out the number of elements or array length
    char *name = NULL;

    getAlgorithmName(algo, &name);//finds the name and later prints it
    printf("%s\n", name);
    printf("%d elements\n", elementsToPrint); 
    printf("%d moves\n", moves);
    printf("%d compares\n\n", compares);

    for(int i = 0; i < elementsToPrint; ++i)//prints out array 
    {
        printf("%d  ", array[i]);
    }

    printf("\n\n");

}

