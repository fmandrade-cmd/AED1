/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Árvore Binária de Busca com Comandos
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Implementar ABB com inserção, busca e percursos
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Nó da Árvore
typedef struct No {
    char valor;
    struct No *esquerda;
    struct No *direita;
} No;

// Cria um novo nó
No* criarNo(char valor) {
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere um valor na árvore binária de busca
No* inserir(No *raiz, char valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    
    return raiz;
}

// Busca um elemento na árvore
int buscar(No *raiz, char valor) {
    if (raiz == NULL) {
        return 0;  // Não encontrado
    }
    
    if (valor == raiz->valor) {
        return 1;  // Encontrado
    } else if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

// Percurso Infixo (Esquerda, Raiz, Direita)
void infixa(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        infixa(raiz->esquerda, primeiro);
        
        if (*primeiro) {
            printf("%c", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %c", raiz->valor);
        }
        
        infixa(raiz->direita, primeiro);
    }
}

// Percurso Prefixo (Raiz, Esquerda, Direita)
void prefixa(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        if (*primeiro) {
            printf("%c", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %c", raiz->valor);
        }
        
        prefixa(raiz->esquerda, primeiro);
        prefixa(raiz->direita, primeiro);
    }
}

// Percurso Posfixo (Esquerda, Direita, Raiz)
void posfixa(No *raiz, int *primeiro) {
    if (raiz != NULL) {
        posfixa(raiz->esquerda, primeiro);
        posfixa(raiz->direita, primeiro);
        
        if (*primeiro) {
            printf("%c", raiz->valor);
            *primeiro = 0;
        } else {
            printf(" %c", raiz->valor);
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
    char comando[10];
    char elemento;
    No *raiz = NULL;
    
    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "I") == 0) {
            // Inserir elemento
            scanf(" %c", &elemento);
            raiz = inserir(raiz, elemento);
        } 
        else if (strcmp(comando, "INFIXA") == 0) {
            // Percurso Infixo
            int primeiro = 1;
            infixa(raiz, &primeiro);
            printf("\n");
        } 
        else if (strcmp(comando, "PREFIXA") == 0) {
            // Percurso Prefixo
            int primeiro = 1;
            prefixa(raiz, &primeiro);
            printf("\n");
        } 
        else if (strcmp(comando, "POSFIXA") == 0) {
            // Percurso Posfixo
            int primeiro = 1;
            posfixa(raiz, &primeiro);
            printf("\n");
        } 
        else if (strcmp(comando, "P") == 0) {
            // Pesquisar elemento
            scanf(" %c", &elemento);
            if (buscar(raiz, elemento)) {
                printf("%c existe\n", elemento);
            } else {
                printf("%c nao existe\n", elemento);
            }
        }
    }
    
    // Libera a memória
    liberarArvore(raiz);
    
    return 0;
}
