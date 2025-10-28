/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre 
 * Projeto:    Exercícios que compõem a nota da UC
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       27/10/2025
 *
 * Arquivo:    1548.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int valor;
    struct cel *prox;
}Celula;

void inserirCelulaLista(int valor, Celula **es, Celula **et){
    Celula *nova;
    nova = (Celula *)malloc(sizeof(Celula));

    if(nova == NULL){
        printf("Erro de alocação!");
        return;
    }

    nova->valor = valor;
    nova->prox = NULL;

    if(*et == NULL){
        *et = *es = nova;
    }else{
        (*et)->prox = nova; //Adicona célula no final
        *et = nova; //Atualiza o ponteiro de referência *et para a célula nova
    }
}

void reordenarLista(Celula **es){
    Celula *i, *j;
    int temp;

    for(i = *es; i != NULL; i = i->prox){
        for(j = i->prox; j != NULL; j = j->prox){
            if(i->valor < j->valor){
                temp = i->valor;
                i->valor = j->valor;
                j->valor = temp;
            }
        }
    }
}

void liberarLista(Celula **es, Celula **et) {
    Celula *p = *es;
    Celula *temp;
    
    while (p != NULL) {
        temp = p;
        p = p->prox;
        free(temp);
    }
    
    *es = NULL;
    *et = NULL;
}

int main(){

    int N, M, P, cont;
    Celula *s, *t;

    scanf("%d", &N);
    for(int i = 0; i < N;  i++){
        s = t = NULL;
        cont = 0;
        //Número M de alunos
        scanf("%d", &M);
        int original[M];
        for(int m = 0; m < M; m++){
            scanf("%d", &P);
            inserirCelulaLista(P, &s, &t);
            original[m] = P;
        }
        reordenarLista(&s);

        Celula *p = s;

        for(int j = 0; j < M; j++){
            if(original[j] == p->valor){
                cont++;
            }
            p = p->prox;
        }

        printf("%d\n", cont);
        liberarLista(&s, &t);
    }

    return 0;
}
