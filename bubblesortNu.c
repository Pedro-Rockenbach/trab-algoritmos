#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

typedef long long Tdado;
typedef long long Tnum;

static unsigned long long comparacoes = 0, trocas = 0;

void troca(Tdado *x, Tdado *y) {
	Tdado aux = *x;
	*x = *y;
	*y = aux;
}

void escreve(Tdado V[], Tnum n) {
	for (Tnum i = 0; i < n; i++) {
		printf("%lld\n", V[i]);
	}
	printf("\n");
}


void bubbleSort(Tdado dados[], Tnum  n) {
	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
  			comparacoes++;
			if (dados[j] < dados[j - 1]) {
				troca(&dados[j], &dados[j - 1]);
				trocas++;
         	}
		}
   	}
} 

//bubbleSortPior é a função que realiza a ordenação em sentido decrescente a partir da ordenação crescente feita anteriormente
void bubbleSortPior(Tdado dados[], Tnum  n) {
	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
  			comparacoes++;
			if (dados[j] > dados[j - 1]) {
				troca(&dados[j], &dados[j - 1]);
				trocas++;
         	}
      	}
   	}
} 

int main() {
	Tdado *Origem = (Tdado *) malloc(10000000 * sizeof(Tdado));
	Tdado *V = (Tdado *) malloc(10000000 * sizeof(Tdado));

    for(int i = 0; i < 10000000; i++){
		scanf("%llu", &Origem[i]); 
	}

	printf("Algoritmo;Tamanho;Caso;Tempo(s);Comparacoes;Trocas\n");
	unsigned long long MAX = 1000;
    while(MAX <= 10000000){

		//reseta o vetor
		memcpy(V, Origem, MAX * sizeof(Tdado));

		//caso médio
		clock_t inicio_medio = clock();
        bubbleSort(V, MAX);
        clock_t fim_medio = clock();
    	double tempo_medio = (double)(fim_medio - inicio_medio) / CLOCKS_PER_SEC;
		printf("BubbleSort;%lld;Medio;%lf;%lld;%lld\n", MAX, tempo_medio, comparacoes, trocas);
		trocas = comparacoes = 0;    

		//melhor caso
		clock_t inicio_melhor = clock();
        bubbleSort(V, MAX);
        clock_t fim_melhor = clock();
    	double tempo_melhor = (double)(fim_melhor - inicio_melhor) / CLOCKS_PER_SEC;
		printf("BubbleSort;%lld;Melhor;%lf;%lld;%lld\n", MAX, tempo_melhor, comparacoes, trocas);
		trocas = comparacoes = 0; 

		
		//caso pior
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
