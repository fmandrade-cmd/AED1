/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõem a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_insertionsort.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *arr, int n) {
    int i, j, chave;
    
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;
        
        // Move os elementos maiores que a chave uma posição à frente
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void imprimirArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int NC, N;
    int cont = 0;
    
    // Número de Casos de Teste - Cidades
    scanf("%d", &NC);
    
    while (cont < NC) {
        // Número de Pessoas na cidade NC
        scanf("%d", &N);
        
        // Aloca array para armazenar as alturas
        int *alturas = (int *)malloc(N * sizeof(int));
        
        if (alturas == NULL) {
            printf("Erro de alocacao!\n");
            return 1;
        }
        
        // Lê as alturas
        for (int i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }
        
        // Ordena usando Insertion Sort
        insertionSort(alturas, N);
        
        // Imprime o array ordenado
        imprimirArray(alturas, N);
        
        // Libera memória
        free(alturas);
        
        cont++;
    }
    
    return 0;
}
