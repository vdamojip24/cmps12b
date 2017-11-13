# include "common.h"// common header file for all the sorts
# include "mergesort.h"// header file for mergesort.c
# include <stdlib.h>

void merge(int *a, int lena, int *b, int lenb, int *c, int lenc, int *moveCount, int *compares)
{

    if ((lena + lenb) > lenc)//checks to see if the combined lengths is greater than the actual length of the array
    {
        fprintf(stderr, "The destination array has smaller size than the two source arrays. Exiting...\n");//possible error message 
        exit(0);
    }

    int i = 0;//three indexes in the array 
    int j = 0;
    int k = 0;

    while ( (i < lena) && (j < lenb))//checks two separate arrays 
    {
        if (a[i] < b[j])
        {
            c[k++] = a[i++];//sets value and moves to next index in the two arrays
            *moveCount += 1;//keeps track of the number of moves
            *compares = *compares + 1 ;//keeps track of the number of comparisons
        }
        else if (a[i] > b[j])
        {
            c[k++] = b[j++];//sets value and moves to next index in the two arrays
            *moveCount += 1;//keeps track of the number of moves
            *compares = *compares + 1 ;//keeps track of the number of comparisons
        }
        else
        {
            c[k++] = a[i++];//sets value and moves to next index in the two arrays
            c[k++] = b[j++];//sets value and moves to next index in the two arrays
            *moveCount += 2;//keeps track of the number of moves
            *compares = *compares + 2 ;//keeps track of the number of comparisons
        }
    }

    while (i < lena)//checks length of array a
    {
        c[k++] = a[i++];//sets value and moves to next index in the two arrays
        *moveCount += 1;//keeps track of the number of moves
    }

    while (j < lenb)//checks length of array b 
    {
        c[k++] = b[j++];//sets value and moves to next index in the two arrays
        *moveCount += 1;//keeps track of the number of moves
    }
}

void mergeSort(int *array, int len, int *moveCount, int *compares) 
{
    int *temp = (int *)calloc(len , sizeof(int));//allocates memory and sets it to 0

    runMergeSort(array, len, temp, moveCount, compares);//runs the algorithm for the array

    free(temp);//frees up temp memory
}

void runMergeSort(int *array, int len, int *temp, int *moveCount, int *compares) 
{
    if (len <= 1)//checks to make sure the array can be divided in two
    {
        return;
    }

    int mid = len / 2 ;//divides array in two

    runMergeSort(array, mid, temp, moveCount, compares);//recursive method that sorts array
    runMergeSort(array + mid, len - mid,temp + mid, moveCount, compares);//another recirsive method on the second array

    merge(array, mid, array + mid, len - mid, temp, len, moveCount, compares);//merges the two arrays into one 

    for (int i = 0; i < len ; ++i)
    {
        array[i] = temp[i];//sets values into original array
    }

}

#if 0//testing sorting
int main()
{
    //int array[] = {10,50,2,15,7,3,5};
    //int array[] = { 100,90,70,60,50,40,10};
    int array[] = { 1, 2, 3, 4, 5, 6,7};
    int moves = 0;
    int compares = 0;


    mergeSort(array, sizeof(array) / sizeof(int), &moves, &compares);

    printArray(array, sizeof(array)/sizeof(int), sizeof(array)/sizeof(int), compares ,moves, 'M');

    return 0;
}
#endif
