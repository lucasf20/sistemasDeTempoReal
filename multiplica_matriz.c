#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// gcc multiplica_matriz.c -o multiplica_matriz -lpthread

pthread_t threads[16];

typedef struct
{
    int *linha;
    int *coluna;
    int numlinha;
    int numcoluna;
}elementos;

int matriz_resultado[4][4] = {0};

void *multiplica(void * args);
void imprime_matriz(int mat[4][4]);

void main(){
    int matriz_a[4][4], matriz_b[4][4], matriz_b_transp[4][4], rstatus, aux;
    elementos argumentos[16];

    srand(time(NULL));
    for(int i = 0; i<4; i++){ //criando duas matrizes de inteiros aleatorias 4x4
        for(int j = 0; j < 4; j++){
            matriz_a[i][j] = rand()%100 - rand()%100;
            matriz_b[i][j] = rand()%100 - rand()%100;
            matriz_b_transp[j][i] = matriz_b[i][j];
        }
    }
    aux = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            argumentos[aux].linha = matriz_a[i];
            argumentos[aux].coluna = matriz_b_transp[j];
            argumentos[aux].numlinha = i;
            argumentos[aux].numcoluna = j;
            rstatus = pthread_create(&threads[aux], NULL, multiplica, &argumentos[aux]);
            aux++;
            if(rstatus != 0){
                printf("Erro ao criar thread!\n");
                exit(EXIT_FAILURE);
            }
        }
    } 

    for(int i = 0; i < 16; i++){
        rstatus = pthread_join(threads[i], NULL);
        if(rstatus != 0){
            printf("Erro ao finalizar thread!\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Matriz A: \n");
    imprime_matriz(matriz_a);
    printf("\nMatriz B: \n");
    imprime_matriz(matriz_b);
    printf("\nA multiplicacao dessas matrizes resulta em:\n");
    imprime_matriz(matriz_resultado);
}

void *multiplica(void * arg){
    elementos *args =(elementos *) arg;

    for(int i = 0; i < 4; i++){
        matriz_resultado[args->numlinha][args->numcoluna] += (args->linha[i]*args->coluna[i]);
    }
    pthread_exit(NULL);
}

void imprime_matriz(int mat[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%i      ", mat[i][j]);
        }
        printf("\n");
    }
}