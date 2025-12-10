/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõem a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_mergesort.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int esq, int meio, int dir) {
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    // Arrays temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    if (L == NULL || R == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }
    
    // Copia dados para os arrays temporários
    for (i = 0; i < n1; i++) {
        L[i] = arr[esq + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[meio + 1 + j];
    }
    
    // Mescla os arrays temporários de volta ao array original
    i = 0;
    j = 0;
    k = esq;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Libera memória dos arrays temporários
    free(L);
    free(R);
}

void mergeSort(int *arr, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        // Ordena primeira e segunda metades
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        
        // Mescla as metades ordenadas
        merge(arr, esq, meio, dir);
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
        
        // Ordena usando Merge Sort
        mergeSort(alturas, 0, N - 1);
        
        // Imprime o array ordenado
        imprimirArray(alturas, N);
        
        // Libera memória
        free(alturas);
        
        cont++;
    }
    
    return 0;
}
