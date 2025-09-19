/*
    Fazer o exercício 1180 usando ponteiros e métodos de alocação de memória (MALLOC)
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int tamanho;
    
    scanf("%d", &tamanho);

    int *vetor = (int*) malloc(tamanho * sizeof(int));

    if (vetor == NULL){
        printf("erro de alocação");
        return 1;
    }

    for (int i = 0; i < tamanho; i++){
        scanf("%d", &vetor[i]);
    }

    int menor = vetor[0];
    int posicao = 0;

    for (int i = 1; i < tamanho; i++){
        if (vetor[i] < menor){
            menor = vetor[i];
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    free(vetor);

    return 0;
}
