#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1000005

// Definição do nó da Pilha
typedef struct No {
    char *joia;
    struct No *proximo;
} No;

// Estrutura de controlo da Pilha
typedef struct {
    No *topo;
    int tamanho;
} Pilha;

// Inicializa a pilha
void inicializar(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

// Empilha (Push) uma nova joia
void push(Pilha *p, char *texto) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        exit(1); // Erro de alocação
    }
    
    // Aloca memória para a string e copia
    novo->joia = (char *)malloc((strlen(texto) + 1) * sizeof(char));
    strcpy(novo->joia, texto);
    
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

// Desempilha (Pop) uma joia
// Retorna a string (o utilizador deve libertar a memória depois)
char* pop(Pilha *p) {
    if (p->topo == NULL) return NULL;
    
    No *temp = p->topo;
    char *dado = temp->joia;
    
    p->topo = temp->proximo;
    p->tamanho--;
    
    free(temp); // Liberta o nó, mas não a string
    return dado;
}

// Função de comparação para o qsort
int comparar(const void *a, const void *b) {
    const char **strA = (const char **)a;
    const char **strB = (const char **)b;
    return strcmp(*strA, *strB);
}

int main() {
    char buffer[MAX_BUFFER];
    Pilha pilha;
    inicializar(&pilha);
    
    // 1. Leitura: Armazenar todas as joias na pilha
    while (scanf("%s", buffer) != EOF) {
        push(&pilha, buffer);
    }
    
    int n = pilha.tamanho;
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    // 2. Transferência: Passar da pilha para um vetor para ordenar
    // (A ordenação é necessária para contar distintos eficientemente)
    char **lista_joias = (char **)malloc(n * sizeof(char *));
    
    for (int i = 0; i < n; i++) {
        lista_joias[i] = pop(&pilha);
    }
    
    // 3. Ordenação
    qsort(lista_joias, n, sizeof(char *), comparar);
    
    // 4. Contagem de distintos
    int distintos = 1;
    for (int i = 1; i < n; i++) {
        if (strcmp(lista_joias[i], lista_joias[i-1]) != 0) {
            distintos++;
        }
    }
    
    printf("%d\n", distintos);
    
    // 5. Limpeza de memória
    for (int i = 0; i < n; i++) {
        free(lista_joias[i]);
    }
    free(lista_joias);
    
    return 0;
}
