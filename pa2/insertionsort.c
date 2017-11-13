# include "common.h"// common header file for all the sorts
# include "insertionsort.h"//header file for insertion sort

void insertionSort(int *array, int len, int *moveCount, int *compares) 
{
    int i = 0;
    int j = 0;

    for (i = 1; i < len; ++i)
    {
        int num = array[i];//sets index to second element of array
        int swapIndex = -1;//initializes an index to swap
        for (j = i -1; j >= 0 ; --j)
        {
            (*compares)++;//keeps track of the number comparisons
            if (num < array[j])
            {
                swapIndex = j;//sets the swap index to jth index of the array
                array[j + 1] = array[j];//switches two elements
                (*moveCount)++;//increments the amount of moves 
            }
            else
            {
                break;//breaks from previous loop to move on 
            }
        }
        if (swapIndex != -1)//
        {
            array[swapIndex] = num;//sets the swapIndex's element to the value at array[i]
            (*moveCount)++;//increments the amount of moves 
        }
    }
}