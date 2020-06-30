#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// gcc numeros_primos_thread.c -o numeros_primos_thread -lpthread

pthread_t threads[10];

typedef struct
{
    int comeco;
    int fim;
} intervals;

void *primos(void *args);

void main(){
    int rstatus;
    intervals dados[10];
    clock_t t1,t2;

    t1 = clock();
    for(int i = 0; i < 10; i++){
        dados[i].comeco = i*10000;
        dados[i].fim = dados[i].comeco + 10000;
        rstatus = pthread_create(&threads[i], NULL, primos, &dados[i]);
        if(rstatus != 0){
            printf("Erro ao criar thread!\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 10; i++){
        rstatus = pthread_join(threads[i], NULL);
        if(rstatus != 0){
            printf("Erro ao finalizar thread!\n");
            exit(EXIT_FAILURE);
        }
    }

    t2 = clock();

    printf("\nO tempo total foi: %f segundos\n", (double)(t2-t1)/CLOCKS_PER_SEC);

}

void *primos(void *args){
    intervals *arg = (intervals *) args;
    for(int i = arg->comeco; i < arg->fim; i++){
        for(int n = 2; n <= i; n++){
            if(n == i){
                printf("%i eh um numero primo\n", i);
            }
            if( i % n == 0){
                break;
            }
        }
    }
    pthread_exit(NULL);
}