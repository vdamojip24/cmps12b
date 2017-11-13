# include "common.h"//common header file for all sorts
# include "bubblesort.h"// header file for bubblesort 

void bubbleSort(int *array, int len, int *moveCount, int *compares) 
{
    for (int i = 0; i < len; ++i)
    {
        int flag = 0;//to see when to break out of the program
        for (int j = 0; j < (len - i -1) ; ++j)
        {
            (*compares)++;//keeps track of number of comparisons for final output
            if (array[j] > array[j + 1])//checks side by side elements
            {
                SWAP(array[j], array[j+1], *moveCount);//swaps the two values using swap defined in common.h which also increments the moves
                flag = 1; 
            }
        }

        if (flag == 0)//checks to see when to end the program
            break;
    }
}

#if 0// testing bubbleSort
int main()
{
     int array[] = {10,50,2,15,7,3,5};
    //int array[] = { 100,90,70,60,50,40,10};
    //int array[] = { 1, 2, 3, 4, 5, 6,7};
    int moves = 0;
    int compares = 0;

    bubbleSort(array, sizeof(array) / sizeof(int), &moves, &compares);

    printArray(array, sizeof(array)/sizeof(int), sizeof(array)/sizeof(int), compares ,moves, 'b');

    return 0;
}
#endif
