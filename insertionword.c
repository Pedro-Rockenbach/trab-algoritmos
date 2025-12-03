// insertion_words.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Definição para Strings
#define MAX_CHAR 60 

typedef struct {
    char texto[MAX_CHAR];
} Tdado;

typedef long long Tnum;

// Variáveis globais de contagem
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
		printf("%s\n", V[i].texto);
	}
	printf("\n");
}

/******************************/
/* Função de Inversão Auxiliar */
/******************************/
void inverte_vetor(Tdado dados[], Tnum n) {
    for (Tnum i = 0; i < n / 2; i++) {
        troca(&dados[i], &dados[n - 1 - i]);
    }
}

/***************************************/
/* Insertion Sort Adaptado para Strings*/
/***************************************/
void insertionSort(Tdado dados[], Tnum n) {
    Tnum i, j;
    Tdado aux;

    for (i = 1; i < n; i++) {
        aux = dados[i]; // Cópia direta funciona por causa da struct
        
        // Loop modificado para STRINGS
        for (j = i; j > 0; j--) {
            comparacoes++; 
            
            // strcmp(A, B) retorna:
            // < 0 se A vem antes de B
            // > 0 se A vem depois de B (que é o que queremos testar: aux < dados[j-1]?)
            
            // Queremos saber se: aux < dados[j-1]
            // Em "stringuês": strcmp(aux.texto, dados[j-1].texto) < 0
            if (strcmp(aux.texto, dados[j - 1].texto) < 0) {
                dados[j] = dados[j - 1]; // Deslocamento (struct assignment)
                trocas++;
            } else {
                break;
            }
        }
        dados[j] = aux;
        trocas++; // Inserção final
    }
}

/*****************/
/* Função main() */
/*****************/
int main() {
    // Total de palavras no words.txt é ~261.788. 
    // Vamos alocar 300.000 para garantir.
    const unsigned long long TOTAL_ARQUIVO = 300000; 
    
    // Insertion Sort é lento. Para strings é MAIS LENTO ainda.
    // Sugiro um limite menor para testes iniciais (ex: 20.000 ou 50.000).
    // Se tiver paciência, deixe rodar até o final.
    const unsigned long long LIMITE_TESTE = 50000; 
    const unsigned long long PASSO = 1000;

    Tdado *vetorOrigem = (Tdado *) malloc(TOTAL_ARQUIVO * sizeof(Tdado));
    Tdado *vetorTeste = (Tdado *) malloc(TOTAL_ARQUIVO * sizeof(Tdado));
    
    if (!vetorOrigem || !vetorTeste) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    // Leitura do arquivo words.txt
    unsigned long long lidos = 0;
    // O scanf com %s lê strings separadas por espaço ou quebra de linha
    while (lidos < TOTAL_ARQUIVO && scanf("%s", vetorOrigem[lidos].texto) == 1) {
        lidos++;
    }

    printf("Algoritmo;Tamanho;Caso;Tempo(s);Comparacoes;Trocas\n");

    for (unsigned long long n = PASSO; n <= lidos; n += PASSO) {
        if (n > LIMITE_TESTE) break; 

        // --- CASO MÉDIO ---
        // Copia dados originais
        for(unsigned long long k=0; k<n; k++) vetorTeste[k] = vetorOrigem[k];
        
        comparacoes = 0; trocas = 0;
        clock_t inicio = clock();
        insertionSort(vetorTeste, n); 
        clock_t fim = clock();
        printf("InsertionString;%llu;Medio;%f;%llu;%llu\n", n, (double)(fim - inicio) / CLOCKS_PER_SEC, comparacoes, trocas);

        // --- MELHOR CASO ---
        // Vetor já está ordenado do passo anterior
        comparacoes = 0; trocas = 0;
        inicio = clock();
        insertionSort(vetorTeste, n); 
        fim = clock();
        printf("InsertionString;%llu;Melhor;%f;%llu;%llu\n", n, (double)(fim - inicio) / CLOCKS_PER_SEC, comparacoes, trocas);

        // --- PIOR CASO ---
        inverte_vetor(vetorTeste, n);
        comparacoes = 0; trocas = 0;
        inicio = clock();
        insertionSort(vetorTeste, n); 
        fim = clock();
        printf("InsertionString;%llu;Pior;%f;%llu;%llu\n", n, (double)(fim - inicio) / CLOCKS_PER_SEC, comparacoes, trocas);
        
        // Se quiser ver se está funcionando, descomente abaixo na primeira iteração:
        if (n == 1000) escreve(vetorTeste, 10); 
    }
    
    free(vetorOrigem);
    free(vetorTeste);
    return 0;
}
