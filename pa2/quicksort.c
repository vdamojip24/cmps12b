# include "common.h"//common header file for all sorts
# include "quicksort.h"//header file for quicksort

void quickSort(int *array, int len, int *moveCount, int *compares) 
{
    if (len <= 1)//checks to see if array can be partitioned
        return;

    int partitionIndex = 0;//initializes partition index
    int pivot = array[len - 1];//initializes pivot value to last element in the array
    partition(array, len -1, pivot, moveCount, compares, &partitionIndex); 
    SWAP(array[partitionIndex],array[len-1], *moveCount);//swaps the two elements

    quickSort(array, partitionIndex, moveCount, compares);//recursive method on first half of array
    quickSort(array + partitionIndex, len - partitionIndex, moveCount, compares);//recursive method on second half of array
}

void partition(int *array, int len, int pivot, int *moveCount, int *compares ,int *partitionIndex)
{
    int j = len - 1;
    int i = 0;

    //sorts array into two halves 
    while ( i <= j) 
    {
        while (array[i] < pivot) 
        {
            *compares += 1;//keeps track of comparisons
            i++;//moves to next index in array
        }

        *compares += 1;//keeps track of comparisons

        while(array[j] > pivot)
        {
            *compares += 1;//keeps track of comparisons
            j--;//moves to next(moves left) index in array
        }
        
        *compares += 1;//keeps track of comparisons

        if ( i < j)
        {
            SWAP(array[i], array[j], *moveCount);//swaps the two elements
            i++;//moves to next index in array
            j--;//moves to next(moves left) index in array
        }
    }

    *partitionIndex = i;//sets the partition index 
}

#if 0//testing sorting
int main()
{
    // int array[] = {10,50,2,15,7,3,5};
    //int array[] = { 100,90,70,60,50,40,10};
//    int array[] = { 1, 2, 3, 4, 5, 6,7};
int array[] = {47320,272862,813325,931036,1300149,1451478,1482116,
1599339,1886666,1926530,1999678,2177992,2338129,2381540,
2504306,2752788,2996335,2998169,3171889,3590861,3829897,
3967508,4022167,4231676,4422014,4702258,4742819,4841493,
4915648,5160950,5607401,5792480,5812062,5967954,5968964,
6053032,6195346,6301066,6375315,6389795,6781764,6797856,
7260963,7261776,7443963,7614058,7685040,7685284,7739256,
7989314,8075396,8085360,8249909,8352629,8737396,9017069,
9214736,9256511,9320602,9414691,9489446,9526978,9657331,
10177720,10578757,10623131,10856398,10978990,11215204,11268563,
11339313,11464349,11556747,11680696,11697687,11774380,11989481,
12291309,12547422,12617960,12814415,12844019,12899314,12912456,
13059818,13226807,13494413,13782527,14314674,14404909,14506627,
14956880,15232419,15509585,15563419,15846433,15950040,16608657,
16703976,16712977};

    int moves = 0;
    int compares = 0;

    quickSort(array, sizeof(array) / sizeof(int), &moves, &compares);

    printArray(array, sizeof(array)/sizeof(int), sizeof(array)/sizeof(int), compares ,moves, 'q');

    return 0;
}
#endif
