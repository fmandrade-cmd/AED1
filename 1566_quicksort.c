/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõem a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_quicksort.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int *arr, int baixo, int alto) {
    int pivo = arr[alto];    // Escolhe o último elemento como pivô
    int i = (baixo - 1);     // Índice do menor elemento
    int j;
    
    for (j = baixo; j <= alto - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

void quickSort(int *arr, int baixo, int alto) {
    if (baixo < alto) {
        // pi é o índice de particionamento
        int pi = particionar(arr, baixo, alto);
        
        // Ordena elementos antes e depois da partição
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
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
        
        // Ordena usando Quick Sort
        quickSort(alturas, 0, N - 1);
        
        // Imprime o array ordenado
        imprimirArray(alturas, N);
        
        // Libera memória
        free(alturas);
        
        cont++;
    }
    
    return 0;
}
