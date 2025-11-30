/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Estação de Trem
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Verificar se é possível reorganizar vagões usando uma pilha (estação)
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

// Estrutura da Pilha (Estação)
typedef struct {
    int dados[MAX];
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

// Empilha um elemento
void push(Pilha *p, int vagao) {
    if (p->topo < MAX - 1) {
        p->dados[++(p->topo)] = vagao;
    }
}

// Desempilha um elemento
int pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->dados[(p->topo)--];
    }
    return -1;
}

// Retorna o topo sem remover
int topo(Pilha *p) {
    if (!estaVazia(p)) {
        return p->dados[p->topo];
    }
    return -1;
}

// Verifica se é possível reorganizar os vagões
int podeReorganizar(int n, int *saida) {
    Pilha estacao;
    inicializaPilha(&estacao);
    
    int vagaoChegando = 1;  // Próximo vagão que chegará da direção A (1, 2, 3, ..., n)
    
    // Para cada vagão na ordem de saída desejada
    for (int i = 0; i < n; i++) {
        int vagaoDesejado = saida[i];
        
        // Se o vagão desejado está no topo da estação, retira
        if (!estaVazia(&estacao) && topo(&estacao) == vagaoDesejado) {
            pop(&estacao);
        } 
        else {
            // Precisa trazer vagões da direção A até encontrar o desejado
            while (vagaoChegando <= n && vagaoChegando != vagaoDesejado) {
                push(&estacao, vagaoChegando);
                vagaoChegando++;
            }
            
            // Se encontrou o vagão desejado chegando
            if (vagaoChegando == vagaoDesejado) {
                vagaoChegando++;  // Esse vagão vai direto para B (não entra na estação)
            } 
            // Se o vagão desejado ainda está na estação
            else if (!estaVazia(&estacao) && topo(&estacao) == vagaoDesejado) {
                pop(&estacao);
            } 
            // Se não conseguiu obter o vagão desejado
            else {
                return 0;  // Impossível
            }
        }
    }
    
    return 1;  // Possível
}

int main() {
    int n;
    
    while (scanf("%d", &n) != EOF && n != 0) {
        int saida[MAX];
        int primeiroBloco = 1;
        
        while (1) {
            // Lê o primeiro número da permutação
            scanf("%d", &saida[0]);
            
            // Se for 0, termina este bloco
            if (saida[0] == 0) {
                printf("\n");  // Linha em branco após cada bloco
                break;
            }
            
            // Lê o restante da permutação
            for (int i = 1; i < n; i++) {
                scanf("%d", &saida[i]);
            }
            
            // Verifica se é possível reorganizar
            if (podeReorganizar(n, saida)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }
    
    return 0;
}
