/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõesm a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Arquivo:    1566_binarytree.c
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>

typedef struct leaf{
    int altura;
    struct leaf *dir;
    struct leaf *esq;
}Folha;

typedef Folha *Arvore;

Folha *NovaFolha (int altura){
    Folha *folha;
    folha = (Folha *)malloc(sizeof(Folha));
    folha->altura = altura;
    folha->dir = NULL;
    folha->esq = NULL;

    return folha;
}
Arvore InserirBinaryTree (Arvore a, Folha *novo){
    Folha *p, *q;
    
    if(a == NULL){
        return novo;
    }
    p = a;
    while (p != NULL){
        q = p;
        if (novo->altura < p->altura){
            p = p->esq;
        }else{
            p = p->dir;
        } 
    }
    if (novo->altura < q->altura) {
        q->esq = novo;
    }else {
        q->dir = novo;
    }

    return a;

}

void ImprimirBinaryTree (Arvore a, int N){
    Folha *s;
    int t = 0;

    Folha **r = (Folha **)malloc(N * sizeof(Folha *));
    if (r == NULL) { // Checagem de segurança
        printf("Erro de alocacao!\n");
        return;
    }

    if (a == NULL){
        printf("Árvore vazia!");
    }
    s = a;
    while (s != NULL || t > 0){
        if (s != NULL){
            r[t++] = s;
            s = s->esq;
        }else{
            s = r[--t];
            printf ("%d ", s->altura);
            s = s->dir;
        }
    }
    free (r);
}

void liberarArvore(Arvore a) {
    if (a == NULL) {
        return;
    }
    liberarArvore(a->esq);
    liberarArvore(a->dir);
    free(a); // Libera o nó atual SÓ DEPOIS de liberar os filhos
}

int main(){

    int NC, N;
    int cont = 0;
    Folha *f;
    Arvore a;
    //Numero de Casos de Teste - Cidades
    scanf("%d", &NC);

    while (cont < NC){
        a = NULL;
        //Numero de Pessoas na cidade NC
        scanf("%d", &N);
        for (int i = 0; i < N; i++){
            int h = 0;
            //altura de cada pessoa na cidade
            scanf("%d", &h);
            //Criar nova folha
            f = NovaFolha(h);
            a = InserirBinaryTree(a, f);
        }

        ImprimirBinaryTree(a, N);
        printf("\n");

        liberarArvore(a);

        cont++;
    }
    return 0;
}
