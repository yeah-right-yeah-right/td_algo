#include "utils.h"
#include <stdio.h>

bool is_sorted_nondecreasing(int *arr, int n)
{
    for(int i = 1; i<n-1;i++){

        
        if(arr[i-1] > arr[i] || arr[i] > arr[i+1]){
            return 0;
        }
    }
    return 1;
}

int min_int(int a, int b)
{
    if (a<b){
        return a;
    }
    else{
        return b;
    }
}