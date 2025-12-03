// insertionsort.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Declaração do tipo de dado booleano 
typedef long long Tdado;
typedef long long Tnum;

// Variáveis globais estáticas para contar o número de comparações e trocas
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

/******************************/
/* Função para inverter o vetor ordenado*/
/******************************/
// cria o pior caso com base no melhor caso 
void inverte_vetor(Tdado dados[], Tnum n) {
  for (Tnum i = 0; i < n / 2; i++) {
    troca(&dados[i], &dados[n - 1 - i]);
  }
}

/***************************/
/* Ordenação InsertionSort */
/***************************/
void insertionSort(Tdado dados[], Tnum n) {
  Tnum i, j;
  Tdado aux;

  for (i = 1; i < n; i++) {
    aux = dados[i];
    j = i - 1;
    trocas++;

    while (j >= 0) {
      comparacoes++;
      if (dados[j] > aux) {
          dados[j + 1] = dados[j];
          trocas++; 
          j--;
      }
      else {
        break; 
      }
    }
        
    dados[j + 1] = aux;
    trocas++;
  }
}

/*****************/
/* Função main() */
/*****************/
int main() {
  const unsigned long long TOTAL_ARQUIVO = 10000000; 
  const unsigned long long LIMITE_TESTE = 10000000; // aqui so pra teste
  const unsigned long long PASSO = 1000;

  // Aloca vetor de origem
  Tdado *vetorOrigem = (Tdado *) malloc(TOTAL_ARQUIVO * sizeof(Tdado));

  // Aloca vetor de teste
  Tdado *vetorTeste = (Tdado *) malloc(TOTAL_ARQUIVO * sizeof(Tdado));
    
  if (vetorOrigem == NULL || vetorTeste == NULL) {
    printf("Erro: Memória insuficiente.\n");
    return 1;
  }

  // le o arquivo inteiro em vez de ler no disco rigido
  unsigned long long lidos = 0;
  while (lidos < TOTAL_ARQUIVO && scanf("%lld", &vetorOrigem[lidos]) == 1) {
    lidos++;
  }

  printf("Algoritmo;Tamanho;Caso;Tempo(s);Comparacoes;Trocas\n");

    // loop de teste de 1000 em 1000
  for (unsigned long long n = PASSO; n <= lidos; n += PASSO) {

    // Para se for muito demorado (O(N^2))
    if (n > LIMITE_TESTE) break; 


    // caso medio
    memcpy(vetorTeste, vetorOrigem, n * sizeof(Tdado));

    // Reseta contadores
    comparacoes = 0;
    trocas = 0;

    clock_t inicio_medio = clock();
    insertionSort(vetorTeste, n); 
    clock_t fim_medio = clock();
    double tempo_medio = (double)(fim_medio - inicio_medio) / CLOCKS_PER_SEC;

    // Imprime resultado
    printf("Insertion;%lld;Medio;%f;%lld;%lld\n", n, tempo_medio, comparacoes, trocas);


    // melhor caso ou seja ordenado
    // Reseta contadores
    comparacoes = 0;
    trocas = 0;

    clock_t inicio_melhor = clock();
    insertionSort(vetorTeste, n); 
    clock_t fim_melhor = clock();
    double tempo_melhor = (double)(fim_melhor - inicio_melhor) / CLOCKS_PER_SEC;

    // Imprime resultado
    printf("Insertion;%lld;Melhor;%f;%lld;%lld\n", n, tempo_melhor, comparacoes, trocas);

    // pior caso ou seja decresscente
    inverte_vetor(vetorTeste, n);

    // Reseta contadores
    comparacoes = 0;
    trocas = 0;

    clock_t inicio_pior = clock();
    insertionSort(vetorTeste, n); 
    clock_t fim_pior = clock();
    double tempo_pior = (double)(fim_pior - inicio_pior) / CLOCKS_PER_SEC;

    // Imprime resultado
    printf("Insertion;%lld;Pior;%f;%lld;%lld\n", n, tempo_pior, comparacoes, trocas);

  }

  // Libera memória
  free(vetorOrigem);
  free(vetorTeste);

  return 0;
}
