#include <stdio.h>

int main(){

    int N, menor, pos, aux;
    

    //printf("Digite um inteiro: ");
    scanf("%d", &N);

    int X[N];

    for(int i = 0; i < N; i++){
        //printf("Digite o %dº valor: ", i + 1);
        scanf("%d", X + i);
    }

    menor = *X;
    pos = 0;

    for(int i = 1; i < N; i++){
        if(*(X + i) < menor){
            menor = *(X + i);
            pos = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", pos);

    return 0;
}
