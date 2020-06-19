#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS 4 //numero de threads
#define VALORMAXIMO 10 //valor maximo dos numeros aleatorios
#define TAMANHODOVETOR 100//tamanho do vetor

// gcc busca_vetor.c -o busca_vetor -lpthread

typedef struct
{
    int *vetor;
    int numero;
    int alcance_de_busca[2];
}dados;

pthread_t threads[NUMTHREADS];

void vetor_aleatorio(int aleatorio[]); // gera o vetor aleatorio de tamanho 100
void *thread_busca_numero(void *arg); // funcao das threads

void main(){
    dados argumentos[NUMTHREADS];
    int rand_arr[TAMANHODOVETOR], numero, resto, aux, rstatus;

    vetor_aleatorio(rand_arr);

    printf("Vetor aleatorio:\n[ ");
    for(int i = 0; i < TAMANHODOVETOR; i++){
        printf("%i ", rand_arr[i]);
    }

    printf("]\nInsira o numero para busca:\n");
    scanf("%i",&numero);

    resto = TAMANHODOVETOR % NUMTHREADS;
    aux = 0;

    for(int i = 0; i < NUMTHREADS; i++){
        argumentos[i].numero = numero;
        argumentos[i].vetor = rand_arr;
        argumentos[i].alcance_de_busca[0] = aux;
        if (resto != 0 && i < resto){
            aux += TAMANHODOVETOR/NUMTHREADS + 1;
        }else{
            aux += TAMANHODOVETOR/NUMTHREADS;
        }
        argumentos[i].alcance_de_busca[1] = aux;
        rstatus = pthread_create(&threads[i], NULL, thread_busca_numero, &argumentos[i]);
        if(rstatus != 0){
            printf("Erro ao criar thread!\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < NUMTHREADS; i++){
        rstatus = pthread_join(threads[i], NULL);
        if(rstatus != 0){
            printf("Erro ao finalizar thread!\n");
            exit(EXIT_FAILURE);
        }
    }
}

void vetor_aleatorio(int aleatorio[]){
    srand(time(NULL));
    for(int i = 0; i < TAMANHODOVETOR; i++){
        aleatorio[i] = rand()%(VALORMAXIMO + 1);
    }
}

void *thread_busca_numero(void *arg){
    dados *args = (dados *)arg;
    for(int i = args->alcance_de_busca[0]; i < args->alcance_de_busca[1]; i++){
        if(args->vetor[i] == args->numero){
            printf("Valor %i encontrado na posicao %i\n", args->numero, i);
        }
    }
    pthread_exit(NULL);
}