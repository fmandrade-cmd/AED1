/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Validação de Parênteses
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Validar se parênteses estão balanceados usando Pilha
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001

// Estrutura da Pilha
typedef struct {
    char dados[MAX];
    int topo;
} Pilha;

// Inicializa a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha está cheia
int estaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Empilha um elemento
void push(Pilha *p, char c) {
    if (!estaCheia(p)) {
        p->topo++;
        p->dados[p->topo] = c;
    }
}

// Desempilha um elemento
char pop(Pilha *p) {
    if (!estaVazia(p)) {
        char c = p->dados[p->topo];
        p->topo--;
        return c;
    }
    return '\0';
}

// Valida se os parênteses estão balanceados
int validaParenteses(char *expressao) {
    Pilha pilha;
    inicializaPilha(&pilha);
    
    int tamanho = strlen(expressao);
    
    for (int i = 0; i < tamanho; i++) {
        char c = expressao[i];
        
        if (c == '(') {
            // Encontrou parêntese que abre: empilha
            push(&pilha, c);
        } 
        else if (c == ')') {
            // Encontrou parêntese que fecha
            if (estaVazia(&pilha)) {
                // Não há parêntese de abertura correspondente
                return 0; // incorrect
            }
            // Remove o parêntese de abertura correspondente
            pop(&pilha);
        }
    }
    
    // Se a pilha está vazia, todos os parênteses estão balanceados
    return estaVazia(&pilha);
}

int main() {
    char expressao[MAX];
    
    // Lê expressões até o fim do arquivo
    while (fgets(expressao, MAX, stdin) != NULL) {
        // Remove o caractere de nova linha se existir
        int len = strlen(expressao);
        if (len > 0 && expressao[len - 1] == '\n') {
            expressao[len - 1] = '\0';
        }
        
        // Valida a expressão
        if (validaParenteses(expressao)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
    
    return 0;
}
