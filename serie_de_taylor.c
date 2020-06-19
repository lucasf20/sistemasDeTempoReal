#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//gcc serie_de_taylor.c -o serie_de_taylor -lm -lpthread

pthread_t threads[2];

typedef struct
{
    char funcao;
    float x;
    double res;
}dados;


void *calc_taylor(void *arg);
float fatorial (float n);

void main(){
    int rstatus;
    float x, fx;
    float *f1, *f2;
    dados argumentos[2];
    puts("Insira o valor de x: ");
    scanf("%f", &x);
    argumentos[0].funcao = 's';
    argumentos[1].funcao = 'c';
    argumentos[0].x = x;
    argumentos[1].x = x;
    for(int i = 0; i < 2; i++){
        rstatus = pthread_create(&threads[i], NULL, calc_taylor, &argumentos[i]);
        if(rstatus != 0){
            printf("Erro ao criar thread!\n");
            exit(EXIT_FAILURE);
        }
    }
    rstatus = pthread_join(threads[0],NULL);
    if(rstatus != 0){
        printf("Erro ao finalizar thread!\n");
        exit(EXIT_FAILURE);
    }
    rstatus = pthread_join(threads[1],NULL);
    if(rstatus != 0){
        printf("Erro ao finalizar thread!\n");
        exit(EXIT_FAILURE);
    }
    fx = pow(argumentos[0].res,3) + sqrt(argumentos[1].res);
    printf("\nO valor da funcao com x valendo %f eh: %f\n",x,fx);
}

float fatorial (float n){
    float res = 1;
    while (n > 0){
        res *= n;
        n--;
    }
    return res;
}

void *calc_taylor(void *arg){
    dados *f = (dados *)arg;
    double sum = 0;
    float derivada;
    for(int i = 0; i < 20; i++){
        if(f->funcao == 's'){
            if(i % 4 == 0){
                derivada = sin(0);
            }
            if(i % 4 == 1){
                derivada = cos(0);
            }
            if(i % 4 == 2){
                derivada = -sin(0);
            }
            if(i % 4 == 3){
                derivada = -cos(0);
            }
        }else{
            if(i % 4 == 0){
                derivada = cos(0);
            }
            if(i % 4 == 1){
                derivada = -sin(0);
            }
            if(i % 4 == 2){
                derivada = -cos(0);
            }
            if(i % 4 == 3){
                derivada = sin(0);
            }
        }
        sum += derivada * pow(f->x,i)/fatorial(i);
    }
    f->res = sum;
    pthread_exit(NULL);
}