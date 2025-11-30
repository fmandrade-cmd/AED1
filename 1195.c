/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Árvore Binária de Busca
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Construir ABB e realizar percursos (pré-ordem, in-ordem, pós-ordem)
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó da Árvore
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;

// Cria um novo nó
No* criarNo(int valor) {
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere um valor na árvore binária de busca
No* inserir(No *raiz, int valor) {
    // Se a árvore está vazia, cria a raiz
    if (raiz == NULL) {
        return criarNo(valor);
    }
    
    // Se o valor é menor, vai para a esquerda
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    // Se o valor é maior, vai para a direita
    else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    
    return raiz;
}

// Percurso em Pré-Ordem (Raiz, Esquerda, Direita)
void preOrdem(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        if (*primeiro) {
            printf("%d", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %d", raiz->valor);
        }
        preOrdem(raiz->esquerda, primeiro);
        preOrdem(raiz->direita, primeiro);
    }
}

// Percurso em In-Ordem (Esquerda, Raiz, Direita)
void inOrdem(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerda, primeiro);
        if (*primeiro) {
            printf("%d", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %d", raiz->valor);
        }
        inOrdem(raiz->direita, primeiro);
    }
}

// Percurso em Pós-Ordem (Esquerda, Direita, Raiz)
void posOrdem(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda, primeiro);
        posOrdem(raiz->direita, primeiro);
        if (*primeiro) {
            printf("%d", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %d", raiz->valor);
        }
    }
}

// Libera a memória da árvore
void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    int C, N, valor;
    
    scanf("%d", &C);
    
    for (int caso = 1; caso <= C; caso++) {
        scanf("%d", &N);
        
        No *raiz = NULL;
        
        // Constrói a árvore
        for (int i = 0; i < N; i++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }
        
        // Imprime o caso
        printf("Case %d:\n", caso);
        
        // Percurso Pré-Ordem
        printf("Pre.:");
        int primeiro = 1;
        if (raiz != NULL) {
            printf(" ");
            preOrdem(raiz, &primeiro);
        }
        printf("\n");
        
        // Percurso In-Ordem
        printf("In..:");
        primeiro = 1;
        if (raiz != NULL) {
            printf(" ");
            inOrdem(raiz, &primeiro);
        }
        printf("\n");
        
        // Percurso Pós-Ordem
        printf("Post:");
        primeiro = 1;
        if (raiz != NULL) {
            printf(" ");
            posOrdem(raiz, &primeiro);
        }
        printf("\n");
        
        // Linha em branco após cada caso
        printf("\n");
        
        // Libera a memória
        liberarArvore(raiz);
    }
    
    return 0;
}
