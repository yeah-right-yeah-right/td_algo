#include <math.h>
#include <stdio.h>
#include "search.h"
#include "utils.h"

int linear_search(int *arr, int n, int target)
{
    // linear search, return index of target
    // return -1 if not found
    for (int i = 0; i<n; i++){
        if (arr[i] == target){
            return i;
        }
    }

    return -1;
}

int jump_search(int *arr, int n, int target)
{
    // jump search on sorted array, return index
    // of target, return -1 if not found
    if (!is_sorted_nondecreasing(arr,n)){
        return -1;
    }
    int jump = (int) sqrt(n);
    int found = 0;
    int i = 0;
    while(!found){
        if(arr[i] == target){
            return i;
        }
        if(arr[i] > target){
            i--;
        }
        else{
            i = i + jump;
        }

    }

    return -1;
}

int binary_search(int *arr, int n, int target)
{
    if (!is_sorted_nondecreasing(arr,n)){
        return -1;
    }
    int hi = n;
    int lo = 0;
    int mid;
    // binary search on sorted array, return index
    // of target, return -1 if not found
    while(hi>lo){
        mid = (hi+lo)/2;
        if (arr[mid] == target){
            return mid;
        }
        if (arr[lo] == target){
            return lo;
        }
        if (arr[hi-1] == target){
            return hi-1;
        }
        if (arr[mid] > target){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    
    return -1;
}
