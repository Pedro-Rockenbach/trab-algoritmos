#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX_PALAVRA 50
#define TOTAL_PALAVRAS 261788

typedef struct {
    char texto[TAM_MAX_PALAVRA];
} Tdado;

typedef long long Tnum;

static unsigned long long comparacoes = 0, trocas = 0;

void troca(Tdado *x, Tdado *y) {
    Tdado aux = *x;
    *x = *y;
    *y = aux;
}

void bubbleSort(Tdado dados[], Tnum n) {
    for (int i = 0; i < n - 1; i++) {
        for(int j = n - 1; j > i; j--) {
            comparacoes++;
            if (strcmp(dados[j].texto, dados[j - 1].texto) < 0) {
                troca(&dados[j], &dados[j - 1]);
                trocas++;
            }
        }
    }
} 

void bubbleSortPior(Tdado dados[], Tnum n) {
    for (int i = 0; i < n - 1; i++) {
        for(int j = n - 1; j > i; j--) {
            comparacoes++;
            if (strcmp(dados[j].texto, dados[j - 1].texto) > 0) {
                troca(&dados[j], &dados[j - 1]);
                trocas++;
            }
        }
    }
} 

int main() {
    Tdado *Origem = (Tdado *) malloc(TOTAL_PALAVRAS * sizeof(Tdado));
    Tdado *V = (Tdado *) malloc(TOTAL_PALAVRAS * sizeof(Tdado));

    if (Origem == NULL || V == NULL) {
        return 1;
    }

    int total_lido = 0;
    for(int i = 0; i < TOTAL_PALAVRAS; i++){
        if(scanf("%s", Origem[i].texto) != 1) break; 
        total_lido++;
    }

    printf("Algoritmo;Tamanho;Caso;Tempo(s);Comparacoes;Trocas\n");
    
    unsigned long long MAX = 1000;
    
    while(MAX <= total_lido){

        memcpy(V, Origem, MAX * sizeof(Tdado));

        clock_t inicio_medio = clock();
        bubbleSort(V, MAX);
        clock_t fim_medio = clock();
        double tempo_medio = (double)(fim_medio - inicio_medio) / CLOCKS_PER_SEC;
        printf("BubbleSort;%lld;Medio;%lf;%lld;%lld\n", MAX, tempo_medio, comparacoes, trocas);
        trocas = comparacoes = 0;    

        clock_t inicio_melhor = clock();
        bubbleSort(V, MAX);
        clock_t fim_melhor = clock();
        double tempo_melhor = (double)(fim_melhor - inicio_melhor) / CLOCKS_PER_SEC;
        printf("BubbleSort;%lld;Melhor;%lf;%lld;%lld\n", MAX, tempo_melhor, comparacoes, trocas);
        trocas = comparacoes = 0; 

        clock_t inicio_pior = clock();
        bubbleSortPior(V, MAX);
        clock_t fim_pior = clock();
        double tempo_pior = (double)(fim_pior - inicio_pior) / CLOCKS_PER_SEC;
        printf("BubbleSort;%lld;Pior;%lf;%lld;%lld\n", MAX, tempo_pior, comparacoes, trocas);
        trocas = comparacoes = 0; 

        MAX += 1000;
    }

    free(Origem);
    free(V);
    
    return 0;
}