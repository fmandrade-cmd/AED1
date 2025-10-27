/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre 
 * Projeto:    Exercícios que compõem a nota da UC
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       27/10/2025
 *
 * Arquivo:    2460.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef  struct cel{
    int valor;
    struct cel *prox;
}Celula;

void insereCelulaFila(int valor, Celula **es, Celula **et){
    Celula *nova;
    nova = (Celula *)malloc(sizeof(Celula));

    if (nova == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return;
    }

    nova->valor = valor;
    nova->prox = NULL;
    if (*et == NULL){
        *et = *es = nova;
    }else {
        (*et)->prox = nova;
        *et = nova;
    }
}

// Versão CORRETA da função
void buscaEremoveCelulaFila(int valor, Celula **es, Celula **et){
    Celula *p = *es; // Ponteiro para percorrer (atual)
    Celula *ant = NULL; // Ponteiro para o anterior
    
    while (p != NULL && p->valor != valor) {
        ant = p;       
        p = p->prox;   
    }

    if (p == NULL) { 
        return;
    }
    
    if (ant == NULL) {
        *es = p->prox;
    } else {
        ant->prox = p->prox;
    }
    
    if (p == *et) {
        *et = ant;
    }
    free(p);
}

void imprimeFilaFinal(Celula **es){
    Celula *x;
    x = *es;

    if (x == NULL) {
        printf("[VAZIA]\n");
        return;
    }

    if (x != NULL) { // Verificação de segurança
        printf("%d", x->valor);
        x = x->prox;
    }

    while(x != NULL){
        printf(" %d", x->valor);
        x = x->prox;
    }
}

int main(){

    int N, ident, M, ident_ex;
    Celula *s, *t;

    s = t = NULL;
    //Pede o número N de pessoas na fila
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &ident);
        insereCelulaFila(ident, &s, &t);
    }
    //Pede o número M de pessoas que deixaram a fila
    scanf("%d", &M);
    for(int j = 0; j < M; j++){
        scanf("%d", &ident_ex);
        buscaEremoveCelulaFila(ident_ex, &s, &t);
    }

    imprimeFilaFinal(&s);
    printf("\n");

    return 0;
}
