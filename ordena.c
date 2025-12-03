// ordena.c
// Implementa algoritmos de ordenação

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Declaração do tipo de dado booleano 
typedef enum {false, true} bool;
typedef long long Tdado;
typedef long long Tnum;

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
	printf("[");
	for (Tnum i = 0; i < n; i++) {
		printf("%lld", V[i]);
		if (i < n - 1) {
			printf(", ");
    	}
	}
	printf("]\n");
}

/************************/
/* Ordenação bubbleSort */
/************************/
void bubbleSort(Tdado dados[], Tnum  n) {
	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
			if (dados[j] < dados[j - 1]) {
				troca(&dados[j], &dados[j - 1]);
         }
      }
   }
} 

/************************/
/* Ordenação shakerSort */
/************************/

void shakerSort(Tdado dados[], Tnum n) {
	bool trocou;

	do {
		trocou = false;
		for (Tnum i = (n - 1); i > 0; i--) {
			if(dados[i - 1] > dados[i]) {
				troca(&dados[i - 1], &dados[i]);
            trocou = true;
         }
		}
		for (Tnum i = 1; i < n; i++) {
			if (dados[i - 1] > dados[i]) {
            troca(&dados[i - 1], &dados[i]);
         	trocou = true;
         }
      }
	} while (trocou); 
}

/***************************/
/* Ordenação insertionSort */
/***************************/
void insertionSort(Tdado dados[], Tnum n) {
   for (Tnum i = 1; i < n; i++) {
		Tdado aux = dados[i];
		Tnum j = 0;
      for (j = i; (j > 0) && (aux < dados[j-1]); j--) {
         dados[j] = dados[j - 1];
      }
      dados[j] = aux;
   }
}

/***************************/
/* Ordenação selectionSort */
/***************************/
void selectionSort(Tdado dados[], Tnum n) {
	for (Tnum i = 0; i < (n - 1); i++) {
   	// encontra o menor elemento
		Tnum min = i;
		for (Tnum j = i + 1; j < n; j ++) {
			if (dados[j] < dados[min]) {
				min = j;
         }
      }
      // Troca a posição atual com o menor elemento do vetor
      troca(&dados[min], &dados[i]);
   }
}

/*******************************/
/* Algoritmo merge (mergeSort) */
/*******************************/
void merge(Tdado V[], Tnum low, Tnum mid, Tnum high) {
	Tnum n1 = mid - low + 1; 
	Tnum n2 = high - mid;          
	Tdado left[n1 + 1], right[n2 + 1];
	Tnum i = 0, j = 0;
	
	for (Tnum i = 0; i < n1; i++) {
		left[i] = V[low + i];
   }
	for (Tnum j = 0; j < n2; j++) {
		right[j] = V[mid + 1 + j];
	}
	left[n1] = SHRT_MAX;
	right[n2] = SHRT_MAX;
	
	for (Tnum k = low; k <= high; k++) {
		if (left[i] <= right[j]) {
			V[k] = left[i++];
      } else {
			V[k] = right[j++];
		}
   }
}

/**********************/
/* Ordencão mergeSort */
/**********************/
void mergeSort(Tdado V[], Tnum low, Tnum high) {
	if (low < high) {
		Tnum mid = (low + high) / 2;
		mergeSort(V, low, mid);
		mergeSort(V, mid + 1, high);
		merge(V, low, mid, high);
	}
}

/***********************************/
/* Algoritmo partition (quickSort) */
/***********************************/
int partition(Tnum V[], Tnum low, Tnum high) {
   Tnum pivot = V[low];
   Tnum i = low - 1, j = high + 1;
  
   while (true) {
      do {
         i++;
		} while (V[i] < pivot);
        
      do {
         j--;
      } while (V[j] > pivot);

      if (i >= j) {
         return j;
      }
		troca(&V[i], &V[j]);
   }
}

/***********************/
/* Algoritmo quickSort */
/***********************/
void quickSort(Tnum V[], Tnum low, Tnum high) {
   if (low < high) {
      int pi = partition(V, low, high);  
      quickSort(V, low, pi);
      quickSort(V, pi + 1, high);
   }
}

/***********************/
/* Algoritmo seqSearch */
/***********************/
Tnum seqSearch(Tdado elem, Tdado dados[], Tnum n) {
	Tnum i;
	
   for (i = 0; i < n; i++) {
       if (elem == dados[i])
          return i;   // achou!
   }
	return -1;   // não achou.
}

/***********************/
/* Algoritmo binSearch */
/***********************/
Tnum binSearch(Tdado elem, Tdado dados[], Tnum n) {
   Tnum lo = 0;
   Tnum hi  = n - 1;
   Tnum i = 0;
   
   while (lo <= hi) {
      i = (lo + hi) / 2;
      if (dados[i] == elem) {
         return i; // Achou
      }
      if (elem < dados[i]) {
         hi  = i - 1; // Pesquisa na metade esquerda
      } else {
         lo = i +1; // Pesquisa na metade direita
      }
   }
   return -1;
}

int main() {
   const unsigned long long MAX = 10;
	Tdado V[MAX];
	Tnum n, k, p; // quantidade de números a serem gerados e indice
	clock_t tempo;

	// Imprime o vetor original
	printf("Quantos Elementos (max. %lld)? ", MAX);
	scanf("%lld", &n);	
	srand(time(NULL));	// inicializa o gerador de números aleatórios
	for (int i = 0; i < n; i++) { // gera os números aleatórios
		V[i] = rand() % (3*MAX) + 1;
   }

	printf("Vetor original:\n");
	escreve(V, n);
	
	tempo = clock(); // inicializa a contagem do tempo

	// Ordena o vetor
	// descomente abaixo o algoritmo que deseja testar
	bubbleSort(V, n);
	// shakerSort(V, n);
	// insertionSort(V, n);
	// selectionSort(V, n);
	// mergeSort(V, 0, n - 1);
	// quickSort(V, 0, n - 1);
	
	tempo = clock() - tempo; // fecha a contagem do tempo.

	// Imprime o vetor ordenado
	printf("\nVetor ordenado:\n");
	escreve(V, n);

	// imprime o tempo gasto
	printf("\nTempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);

	// Procura por um elemento aleatório
	k = rand() % (3*MAX) + 1;
	printf("Procurando por %lld...\n", k);

	// Conta o tempo para a busca sequencial
	
	tempo = clock(); // inicializa a contagem do tempo
	// descomente abaixo o algoritmo de busca que deseja usar
	p = seqSearch(k, V, n);
	tempo = clock() - tempo; // fecha a contagem do tempo.
	// imprime o tempo gasto
	printf("\nTempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);
	if (p < 0)
		printf("Não encontrado!\n");
	else
		printf("%llu encontrado na posição %lld.\n", k, p); 

	// Conta o tempo para a busca binária

	tempo = clock(); // inicializa a contagem do tempo
	// descomente abaixo o algoritmo de busca que deseja usar
   p = binSearch(k, V, n);
	tempo = clock() - tempo; // fecha a contagem do tempo.
	// imprime o tempo gasto
	printf("\nTempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);
	if (p < 0)
		printf("Não encontrado!\n");
	else
		printf("%llu encontrado na posição %lld.\n", k, p); 
	return 0;
}
