/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõem a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_selectionsort.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *arr, int n) {
    int i, j, minIdx, temp;
    
    // Percorre todo o array
    for (i = 0; i < n - 1; i++) {
        // Encontra o índice do menor elemento na parte não ordenada
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        // Troca o elemento atual com o menor encontrado
        if (minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
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
        
        // Ordena usando Selection Sort
        selectionSort(alturas, N);
        
        // Imprime o array ordenado
        imprimirArray(alturas, N);
        
        // Libera memória
        free(alturas);
        
        cont++;
    }
    
    return 0;
}
