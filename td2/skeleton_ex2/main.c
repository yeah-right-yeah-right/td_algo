#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "utils.h"

int main(void)
{
    // implement main here
    // create array example using malloc
    // use sorting algorithms and compare runtime
    int arr0[10] = {42, 7, 19, 3, 55, 23, 8, 14, 60, 1};
    printf("pre select: %i\n", is_sorted_nondecreasing(arr0,10));

    selection_sort(arr0,10);

    printf("select: %i\n", is_sorted_nondecreasing(arr0,10));

    int arr01[10] = {42, 7, 19, 3, 55, 23, 8, 14, 60, 1};
    

    printf("pre insert: %i\n", is_sorted_nondecreasing(arr01,10));

    insertion_sort(arr01,10);

    printf("insert: %i\n", is_sorted_nondecreasing(arr01,10));

    int arr02[10] = {42, 7, 19, 3, 55, 23, 8, 14, 60, 1};
    

    printf("pre bubblie: %i\n", is_sorted_nondecreasing(arr02,10));

    bubble_sort(arr02,10);
    
    printf("bubblie: %i\n", is_sorted_nondecreasing(arr02,10));

    int arr1[10] = {42, 7, 19, 3, 55, 23, 8, 14, 60, 1};
    
    /*
    for (int i = 0; i<10; i++){
        printf("%i\n", arr1[i])
    }
        */

    printf("pre merge: %i\n", is_sorted_nondecreasing(arr1,10));

    merge_sort(arr1,10);

    
    printf("merge: %i\n", is_sorted_nondecreasing(arr1,10));

    int arr2[10] = {42, 7, 19, 3, 55, 23, 8, 14, 60, 1};
    

    printf("pre quick: %i\n", is_sorted_nondecreasing(arr2,10));

    quick_sort(arr2,10);

    
    printf("quick: %i\n", is_sorted_nondecreasing(arr2,10));

    return 0;
}
