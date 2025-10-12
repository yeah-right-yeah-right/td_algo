#include<math.h>
#include "prime.h"


int boucle_prime_naif(int n){
    int divisers = 0;
    for (int i = 2; i<n+1; i++){
        if (n%i == 0){
            divisers++;
        }
    }
    if (divisers == 1){
        return 0;
    }
    return 1;
}

void list_primes_naif(int n){
    for (int i = 2; i<n+1; i++){
        if(boucle_prime_naif(i) == 0){
            printf("%i\n", i);
        }
    }
}



void list_primes_efficace(int n){
    int tab[n+1];

    for (int i = 0; i<n+1;i++){
        tab[i] = 0;
    }
    for (int i = 2; i<sqrt(n+1); i++){
        if (tab[i] == 0){
            int j = i*i;
            while (j<n+1){
                tab[j] = 1;
                j+=i;
            }
        }
    }
    for (int i = 2; i<n+1; i++){
        if(tab[i] == 0){
            printf("prime %i\n", i);
        }
    }
}
