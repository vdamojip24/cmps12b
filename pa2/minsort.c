#include "common.h"// common header file for all sorts
#include "minsort.h"// header file for minsort

void minSort(int *array, int len, int *moveCount, int *compares)
{
    *moveCount = 0;//amount of moves made
    *compares = 0;//number of comparisons made

    for (int i = 0; i < (len - 1); ++i)
    {
        for(int j = i + 1; j < len; ++j)
        {
            (*compares)++;
            if (array[j] < array[i])//checks the two elements
            {
                SWAP(array[j], array[i], *moveCount)//swaps the two values and increments the amount of moves
            }
        }
    }

}


#if 0// testing minsort
int main()
{
    // int array[] = {10,50,2,15,7,3,5};
    int array[] = { 100,90,70,60,50,40,10};
    //int array[] = { 1, 2, 3, 4, 5, 6,7};
    int moves = 0;
    int compares = 0;

    minSort(array, sizeof(array) / sizeof(int), &moves, &compares);

printArray(array, sizeof(array)/sizeof(int), sizeof(array)/sizeof(int), compares ,moves, 'm');

    return 0;
}
#endif
