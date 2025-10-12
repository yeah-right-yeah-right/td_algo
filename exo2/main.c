#include<time.h>
#include<stdio.h>
#include "prime.c"





int main(void){

//prime exo 2
    double temps;
    float ms;
    clock_t begin;
    begin = clock();
    list_primes_naif(40);
    
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    ms = temps * 1000.0;

    printf( "Finished primes naif %f ms\n", ms ); 

    begin = clock();
    list_primes_efficace(40);
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    ms = temps * 1000.0;

    printf( "Finished primes efficace %f ms\n", ms ); 


}
