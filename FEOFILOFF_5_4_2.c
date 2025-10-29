#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int valor;
    struct cel *prox;
}Celula;

void InsereListaCircular(int valor, Celula *cabeca, Celula **controle){
    Celula *nova;
    nova = (Celula *)malloc(sizeof(Celula));

    if(nova == NULL){
        printf("Erro de alocação!");
        return;
    }

    nova->valor = valor;

    if(cabeca->prox == NULL){
        nova->prox = cabeca;
        cabeca->prox = nova;
        *controle = nova;
    }else{
        nova->prox = cabeca;
        (*controle)->prox = nova;
        *controle = nova;
    }

}

int main(){

    int N;
    Celula *cabeca, *controle;
    cabeca = (Celula *)malloc(sizeof(Celula));
    cabeca->valor = -1;
    cabeca->prox = NULL;

    controle = NULL;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        InsereListaCircular(i, cabeca, &controle);
    }

    return 0;
}
