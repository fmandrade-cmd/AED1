/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Detector de Estrutura de Dados
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Identificar se operações correspondem a pilha, fila ou fila de prioridade
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

// Estrutura de Pilha
typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

void pushPilha(Pilha *p, int x) {
    if (p->topo < MAX - 1) {
        p->dados[++(p->topo)] = x;
    }
}

int popPilha(Pilha *p) {
    if (p->topo >= 0) {
        return p->dados[(p->topo)--];
    }
    return -1;
}

int vaziaP(Pilha *p) {
    return p->topo == -1;
}

// Estrutura de Fila
typedef struct {
    int dados[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

void inicializaFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
}

void pushFila(Fila *f, int x) {
    if (f->tamanho < MAX) {
        f->dados[f->tras] = x;
        f->tras = (f->tras + 1) % MAX;
        f->tamanho++;
    }
}

int popFila(Fila *f) {
    if (f->tamanho > 0) {
        int valor = f->dados[f->frente];
        f->frente = (f->frente + 1) % MAX;
        f->tamanho--;
        return valor;
    }
    return -1;
}

int vaziaF(Fila *f) {
    return f->tamanho == 0;
}

// Estrutura de Fila de Prioridade (Max Heap)
typedef struct {
    int dados[MAX];
    int tamanho;
} FilaPrioridade;

void inicializaPQ(FilaPrioridade *pq) {
    pq->tamanho = 0;
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void subir(FilaPrioridade *pq, int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (pq->dados[idx] > pq->dados[pai]) {
            trocar(&pq->dados[idx], &pq->dados[pai]);
            idx = pai;
        } else {
            break;
        }
    }
}

void descer(FilaPrioridade *pq, int idx) {
    while (1) {
        int esq = 2 * idx + 1;
        int dir = 2 * idx + 2;
        int maior = idx;
        
        if (esq < pq->tamanho && pq->dados[esq] > pq->dados[maior]) {
            maior = esq;
        }
        if (dir < pq->tamanho && pq->dados[dir] > pq->dados[maior]) {
            maior = dir;
        }
        
        if (maior != idx) {
            trocar(&pq->dados[idx], &pq->dados[maior]);
            idx = maior;
        } else {
            break;
        }
    }
}

void pushPQ(FilaPrioridade *pq, int x) {
    if (pq->tamanho < MAX) {
        pq->dados[pq->tamanho] = x;
        subir(pq, pq->tamanho);
        pq->tamanho++;
    }
}

int popPQ(FilaPrioridade *pq) {
    if (pq->tamanho > 0) {
        int valor = pq->dados[0];
        pq->dados[0] = pq->dados[pq->tamanho - 1];
        pq->tamanho--;
        descer(pq, 0);
        return valor;
    }
    return -1;
}

int vaziaPQ(FilaPrioridade *pq) {
    return pq->tamanho == 0;
}

int main() {
    int n;
    
    while (scanf("%d", &n) != EOF) {
        Pilha pilha;
        Fila fila;
        FilaPrioridade pq;
        
        inicializaPilha(&pilha);
        inicializaFila(&fila);
        inicializaPQ(&pq);
        
        int ehPilha = 1;
        int ehFila = 1;
        int ehPQ = 1;
        
        for (int i = 0; i < n; i++) {
            int comando, x;
            scanf("%d %d", &comando, &x);
            
            if (comando == 1) {
                // Insere em todas as estruturas
                pushPilha(&pilha, x);
                pushFila(&fila, x);
                pushPQ(&pq, x);
            } else {
                // comando == 2: remove e compara
                
                // Testa Pilha
                if (vaziaP(&pilha) || popPilha(&pilha) != x) {
                    ehPilha = 0;
                }
                
                // Testa Fila
                if (vaziaF(&fila) || popFila(&fila) != x) {
                    ehFila = 0;
                }
                
                // Testa Fila de Prioridade
                if (vaziaPQ(&pq) || popPQ(&pq) != x) {
                    ehPQ = 0;
                }
            }
        }
        
        // Determina o resultado
        int count = ehPilha + ehFila + ehPQ;
        
        if (count == 0) {
            printf("impossible\n");
        } else if (count > 1) {
            printf("not sure\n");
        } else if (ehPilha) {
            printf("stack\n");
        } else if (ehFila) {
            printf("queue\n");
        } else {
            printf("priority queue\n");
        }
    }
    
    return 0;
}
