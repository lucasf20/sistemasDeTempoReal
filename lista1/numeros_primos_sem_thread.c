#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// gcc numeros_primos_sem_thread.c -o numeros_primos_sem_thread 

void main(){
    clock_t t1, t2;
    float half;

    t1 = clock();
    for(int i = 0; i<=99999; i++){
        half = i/2;
        for(int n = 2; n <= i; n++){
            if(n > half){
                printf("%i eh um numero primo\n", i);
                break;
            }
            if( i % n == 0){
                break;
            }
        }
    }
    t2 = clock();
    printf("\nO tempo total foi: %f segundos\n", (double)(t2-t1)/CLOCKS_PER_SEC);
}