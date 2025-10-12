#include<time.h>
#include<stdio.h>
#include "fib.c"

int main(void){

    //fibo exo 1
    float ms;
    clock_t begin = clock();
    printf("naif: %i\n", fibo_naif(5));
    clock_t end = clock();
    double temps = (double)(end-begin)/CLOCKS_PER_SEC;
    ms = temps * 1000.0;
    printf( "Finished fibo naif in %f ms\n", ms ); 
    begin = clock();
    printf("dyna: %i\n", fibo_dynamique(5));
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    ms = temps * 1000.0;
    printf( "Finished fibo dyna in %f ms\n", ms ); 

}
