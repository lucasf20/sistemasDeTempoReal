#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// gcc matriz_thread.c -o matriz_thread -lpthread

pthread_t threads[16][16];

typedef struct
{
    int *linha;
    int *coluna;
    int numlinha;
    int numcoluna;
}elementos;

int matriz_resultado[16][16] = {0};

void *multiplica(void * args);
void imprime_matriz(int mat[16][16]);

void main(){
    int matriz_a[16][16], matriz_b[16][16], matriz_b_transp[16][16], rstatus;
    clock_t t1, t2;
    elementos argumentos[16][16];

    srand(time(NULL));
    for(int i = 0; i<16; i++){ //criando duas matrizes de inteiros aleatorias 16x16
        for(int j = 0; j < 16; j++){
            matriz_a[i][j] = rand()%100 - rand()%100;
            matriz_b[i][j] = rand()%100 - rand()%100;
            matriz_b_transp[j][i] = matriz_b[i][j];
        }
    }

    t1 = clock();
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            argumentos[i][j].linha = matriz_a[i];
            argumentos[i][j].coluna = matriz_b_transp[j];
            argumentos[i][j].numlinha = i;
            argumentos[i][j].numcoluna = j;
            rstatus = pthread_create(&threads[i][j], NULL, multiplica, &argumentos[i][j]);
            if(rstatus != 0){
                printf("Erro ao criar thread!\n");
                exit(EXIT_FAILURE);
            }
        }
    } 

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
        rstatus = pthread_join(threads[i][j], NULL);
            if(rstatus != 0){
                printf("Erro ao finalizar thread!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    t2 = clock() - t1;
    printf("Matriz A: \n");
    imprime_matriz(matriz_a);
    printf("\nMatriz B: \n");
    imprime_matriz(matriz_b);
    printf("\nA multiplicacao dessas matrizes resulta em:\n");
    imprime_matriz(matriz_resultado);
    printf("\nTempo total de calculo da multiplicacao de matrizes: %f segundos",(double)(t2)/CLOCKS_PER_SEC);
}

void *multiplica(void * arg){
    elementos *args =(elementos *) arg;

    for(int i = 0; i < 16; i++){
        matriz_resultado[args->numlinha][args->numcoluna] += (args->linha[i]*args->coluna[i]);
    }
    pthread_exit(NULL);
}

void imprime_matriz(int mat[16][16]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            printf("%i      ", mat[i][j]);
        }
        printf("\n");
    }
}