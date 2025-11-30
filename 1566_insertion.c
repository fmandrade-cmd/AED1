#include <stdio.h>
#include <stdlib.h>

// Função clássica do Insertion Sort
void insertionSort(int arr[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;

        // Move os elementos do arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void resolver() {
    int NC; // Número de Cidades
    if (scanf("%d", &NC) != 1) return;

    while (NC--) {
        int N;
        scanf("%d", &N);

        // Alocação dinâmica é necessária pois 3 milhões de inteiros
        // ocupam ~12MB, o que excede o limite padrão da stack (pilha).
        int *alturas = (int*)malloc(N * sizeof(int));
        
        if (alturas == NULL) {
            // Caso falhe a alocação de memória
            exit(1);
        }

        // Leitura dos dados
        for (int i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        // Ordenação usando Insertion Sort
        insertionSort(alturas, N);

        // Impressão dos dados ordenados
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");

        // Liberação da memória
        free(alturas);
    }
}

int main() {
    resolver();
    return 0;
}
