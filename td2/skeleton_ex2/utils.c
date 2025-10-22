#include "utils.h"

void swap_int(int *a, int *b)
{
    int tmp = *a;
    a = b;
    *b = tmp;
}


bool is_sorted_nondecreasing(int *arr, int n)
{
    for(int i = 1; i<n-1;i++){
        if(arr[i-1] > arr[i] || arr[i] > arr[i+1]){
            return 0;
        }
    }
    return 1;
}

void copy_array(int *src, int *dst, int n)
{
    // copy array elements src into dst
}

