/*
    Fazer o exercício 1180 usando ponteiros e métodos de alocação de memória (MALLOC)
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(){
    
    int tamanho;
    
    cin >> tamanho;

    int *vetor = (int*) malloc(tamanho * sizeof(int));

    if (vetor == NULL){
        cout << "erro de alocação" << endl;
        return 1;
    }

    for (int i = 0; i < tamanho; i++){
        cin >> vetor[i];
    }

    int menor = vetor[0];
    int posicao = 0;

    for (int i = 1; i < tamanho; i++){
        if (vetor[i] < menor){
            menor = vetor[i];
            posicao = i;
        }
    }

    cout << "Menor valor: " << menor << endl;
    cout << "Posicao: " << posicao << endl;

    free(vetor);

    return 0;
}
