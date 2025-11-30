/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Extração de Diamantes
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Contar diamantes "<>" usando Pilha
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
        p->dados[++(p->topo)] = c;
    }
}

// Desempilha um elemento
char pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->dados[(p->topo)--];
    }
    return '\0';
}

// Conta a quantidade de diamantes
int contarDiamantes(char *entrada) {
    Pilha pilha;
    inicializaPilha(&pilha);
    
    int diamantes = 0;
    int tamanho = strlen(entrada);
    
    for (int i = 0; i < tamanho; i++) {
        char c = entrada[i];
        
        if (c == '<') {
            // Encontrou abertura de diamante: empilha
            push(&pilha, c);
        } 
        else if (c == '>') {
            // Encontrou fechamento de diamante
            if (!estaVazia(&pilha)) {
                // Há um '<' correspondente na pilha
                pop(&pilha);
                diamantes++;  // Forma um diamante "<>"
            }
            // Se a pilha está vazia, esse '>' não forma diamante
        }
        // Ignora '.' (partículas de areia)
    }
    
    return diamantes;
}

int main() {
    int N;
    char entrada[MAX];
    
    scanf("%d", &N);
    getchar();  // Consome o '\n' após o número
    
    for (int i = 0; i < N; i++) {
        fgets(entrada, MAX, stdin);
        
        // Remove o '\n' se presente
        int len = strlen(entrada);
        if (len > 0 && entrada[len - 1] == '\n') {
            entrada[len - 1] = '\0';
        }
        
        int resultado = contarDiamantes(entrada);
        printf("%d\n", resultado);
    }
    
    return 0;
}
