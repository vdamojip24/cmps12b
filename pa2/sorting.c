//includes all the necessary sorting types as well as necessary libraries
# include <stdio.h>
# include <getopt.h>
# include <stdlib.h>
# include "bubblesort.h"
# include "minsort.h"
# include "mergesort.h"
# include "quicksort.h"
# include "insertionsort.h"
# include "common.h"

int main(int argc, char **argv)
{
    //default values
    char algo = 'A';
    int printNumElems = 100;
    int numElems = 100;
    int seed = 8222022;

    char c;
    while ((c = getopt (argc , argv , "AmbiqMp:r:n:")) != -1)//given by Professor Long
    {
        switch(c)//possible specifications for the program
        {
            case 'A':
                algo = 'A';
            break;

            case 'm':
                algo = 'm';
            break;

            case 'b':
                algo = 'b';
            break;

            case 'i':
                algo = 'i';
            break;

            case 'q':
                algo = 'q';
            break;

            case 'M':
                algo = 'M';
            break;

            case 'p':
                printNumElems = atoi(optarg);// converts "string" into integer
            break;    

            case 'r':
                seed = atoi(optarg);// converts "string" into integer
            break;

            case 'n':
                numElems = atoi(optarg);// converts "string" into integer
            break;

            default:
                fprintf(stderr, "Unknown option: %c\n", c);//stderr for a possible error and prints as well

        }
    }

    fprintf(stdout, "Sorting Algo = %c , seed = %d , numElems = %d printElems = %d\n",
            algo, seed, numElems, printNumElems);//redirect possible error and prints as well

    srand(seed);//pseudorandom numbers

    int *array = calloc(numElems, sizeof(int));//allocates memory and sets memory to 0 

    if (array == NULL)
    {
        fprintf(stderr, "Error allocating the memory. Exiting...\n");//stderr for a possible error and prints as well
        exit(0);
    }

    //Generating the ranmdom numbers
    for(int i = 0; i < numElems; ++i)
    {
        array[i] = rand() % 16777215;
    }

    int moves = 0;
    int compares =0;

    // all of the if statements are for the possible algorithms 
    if ((algo == 'A') || (algo == 'b'))
    {
        moves = 0;
        compares = 0;
        bubbleSort(array, numElems, &moves, &compares);
        printArray(array, numElems,printNumElems , compares ,moves, 'b');
 
    }

    if ((algo == 'A') || (algo == 'm'))
    {
        moves = 0;
        compares = 0;
        minSort(array, numElems, &moves, &compares);
        printArray(array, numElems,printNumElems , compares ,moves, 'm');
    }
    
    if ((algo == 'A') || (algo == 'q'))
    {
        moves = 0;
        compares = 0;
        quickSort(array, numElems, &moves, &compares);
        printArray(array, numElems,printNumElems , compares ,moves, 'q');
    }

    if ((algo == 'A') || (algo == 'i'))
    {
        moves = 0;
        compares = 0;
        insertionSort(array, numElems, &moves, &compares);
        printArray(array, numElems,printNumElems , compares ,moves, 'i');
    }

    if ((algo == 'A') || (algo == 'M'))
    {
        moves = 0;
        compares = 0;
        mergeSort(array, numElems, &moves, &compares);
        printArray(array, numElems,printNumElems , compares ,moves, 'M');
    }

    free(array);//frees up memory
    array = NULL;
    return 0;
}
