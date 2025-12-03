// ordena.c
// Implementa algoritmos de ordenação

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
// Declaração do tipo de dado booleano 
typedef long long Tdado;
typedef long long Tnum;

// variáveis globais estáticas para contar o número de comparações e 
// trocas
static unsigned long long comparacoes = 0, trocas = 0;

/*******************/
/* Função de troca */
/*******************/
void troca(Tdado *x, Tdado *y) {
	Tdado aux = *x;
	*x = *y;
	*y = aux;
}

/*********************/
/* Função de escrita */
/*********************/
void escreve(Tdado V[], Tnum n) {
	for (Tnum i = 0; i < n; i++) {
		printf("%lld\n", V[i]);
	}
	printf("\n");
}

/************************/
/* Ordenação bubbleSort */
/************************/
void bubbleSort(Tdado dados[], Tnum  n) {
	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
  			comparacoes++;	// conta o número de trocas
			if (dados[j] < dados[j - 1]) {
				troca(&dados[j], &dados[j - 1]);
				trocas++;	// conta o número de comparações
         }
      }
   }
} 

/*****************/
/* Função main() */
/*****************/

int main() {
   const unsigned long long MAX = 10;
	Tdado V[MAX];
	clock_t tempo;

	// carrega os dados no vetor
	for (unsigned long long  i = 0; i < MAX; i++) { // gera os números aleatórios
		scanf("%llu", &V[i]); // lê o vetor da entrada
   }

	tempo = clock(); // inicializa a contagem do tempo

	// Ordena o vetor
	bubbleSort(V, MAX);
	
	tempo = clock() - tempo; // fecha a contagem do tempo.

	// Imprime o vetor ordenado
	escreve(V, MAX);

	// imprime o tempo gasto
	printf("\nTempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);

	// imprime o número de comparações
	printf("Comparações: %llu\n", comparacoes);
	// imprime o número de trocas
	printf("Trocas     : %llu\n", trocas);
	return 0;
}
