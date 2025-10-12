#include<time.h>
#include<stdio.h>
#include "prime.c"
#include "fib.c"





int main(void){

    //fibo exo 1
    clock_t begin = clock();
    printf("naif: %i\n", fibo_naif(5));
    clock_t end = clock();
    unsigned long temps = (double)(end-begin)/CLOCKS_PER_SEC;
    printf( "Finished fibo naif in %ld s\n", temps ); 
    begin = clock();
    printf("dynamique: %i\n", fibo_dynamique(5));
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    printf( "Finished fibo dyna in %ld s\n", temps ); 

    //prime exo 2
    begin = clock();
    list_primes_naif(10);
    
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    printf( "Finished primes naif %ld s\n", temps ); 

    begin = clock();
    list_primes_efficace(10);
    end = clock();
    temps = (double)(end-begin)/CLOCKS_PER_SEC;
    printf( "Finished primes efficace %ld s\n", temps ); 


}
