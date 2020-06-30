#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// gcc matriz_sem_thread.c -o matriz_sem_thread

void imprime_matriz(int mat[16][16]);

clock_t t1, t2;

void main(){
    int matriz_a[16][16], matriz_b[16][16], matriz_b_transp[16][16];
    int matriz_resultado[16][16] = {0};

    srand(time(NULL));
    for(int i = 0; i<16; i++){ //criando duas matrizes de inteiros aleatorias 16x16
        for(int j = 0; j < 16; j++){
            matriz_a[i][j] = rand()%100 - rand()%100;
            matriz_b[i][j] = rand()%100 - rand()%100;
            matriz_b_transp[j][i] = matriz_b[i][j];
        }
    }

    t1  = clock();    
    for(int i = 0; i<16; i++){
        for(int j = 0; j<16; j++){
            for(int a = 0; a < 16; a++){
                matriz_resultado[i][j] += matriz_a[i][a]*matriz_b_transp[j][a];
            }
        }
    }
    t2  = clock();

    printf("Matriz A: \n");
    imprime_matriz(matriz_a);
    printf("\nMatriz B: \n");
    imprime_matriz(matriz_b);
    printf("\nA multiplicacao dessas matrizes resulta em:\n");
    imprime_matriz(matriz_resultado);
    printf("\nTempo total de calculo da multiplicacao de matrizes: %f segundos\n",(double)(t2-t1)/CLOCKS_PER_SEC);
}

void imprime_matriz(int mat[16][16]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            printf("%i      ", mat[i][j]);
        }
        printf("\n");
    }
}