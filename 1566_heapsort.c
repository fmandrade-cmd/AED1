/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõem a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_heapsort.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int n, int i) {
    int maior = i;           // Inicializa o maior como raiz
    int esq = 2 * i + 1;     // Filho esquerdo
    int dir = 2 * i + 2;     // Filho direito
    int temp;
    
    // Se o filho esquerdo é maior que a raiz
    if (esq < n && arr[esq] > arr[maior]) {
        maior = esq;
    }
    
    // Se o filho direito é maior que o maior até agora
    if (dir < n && arr[dir] > arr[maior]) {
        maior = dir;
    }
    
    // Se o maior não é a raiz
    if (maior != i) {
        temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        
        // Recursivamente heapifica a subárvore afetada
        heapify(arr, n, maior);
    }
}

void heapSort(int *arr, int n) {
    int i, temp;
    
    // Constrói o heap (reorganiza o array)
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extrai elementos do heap um por um
    for (i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Chama heapify na heap reduzida
        heapify(arr, i, 0);
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
        
        // Ordena usando Heap Sort
        heapSort(alturas, N);
        
        // Imprime o array ordenado
        imprimirArray(alturas, N);
        
        // Libera memória
        free(alturas);
        
        cont++;
    }
    
    return 0;
}
