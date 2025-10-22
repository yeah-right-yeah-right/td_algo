#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"
#include "utils.h"

int main(void)
{
    // implement main here
    // create array example using malloc
    // use searching algorithms and compare runtime
    int * arr = malloc(3*sizeof(int));
    arr[0] = 0; arr[1] = 3; arr[2] = 2;
    printf("%i\n", linear_search(arr, 3, 2));
    printf("%i\n", jump_search(arr, 3, 2));
    printf("%i\n", binary_search(arr, 3, 2));



    return 0;
}
