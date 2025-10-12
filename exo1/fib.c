#include "fib.h"

int fibo_naif(int n){
    if(n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    else{
        return fibo_naif(n-1) + fibo_naif(n-2);
    }
}

int fibo_dynamique(int n){
    int tab[n+1];
    tab[0] = 0;
    tab[1] = 1;
    for(int i = 2; i<n+1; i++){
        tab[i] = tab[i-1] + tab[i-2];
    }
    return tab[n];
}
