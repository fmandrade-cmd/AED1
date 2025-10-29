/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõesm a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    Feofiloff_5_4_3.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    struct cel *ant;
    int valor;
    struct cel *prox;
}Celula;

void InserirDoubleLinkedList(int valor, Celula **inicio, Celula **fim){

    Celula *nova;
    nova = (Celula *)malloc(sizeof(Celula));

    if(nova == NULL){
        printf("Erro de alocação");
        return;
    }
    
    nova->valor = valor;
    nova->prox = NULL;

    if(*fim == NULL){
        nova->ant = NULL;
        *fim = *inicio = nova;
    }else{
        (*fim)->prox = nova;
        nova->ant = *fim;
        *fim = nova;
    }
}

int main(){

    int N;
    Celula *i, *f;
    i = f = NULL;

    scanf("%d",&N);

    for(int j = 0; j < N; j++){
        InserirDoubleLinkedList(j, &i, &f);
    }

    return 0;
}