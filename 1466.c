#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
} Node;

// Função para criar um novo nó
Node* criarNode(int valor) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->valor = valor;
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;
    return novoNode;
}

// Função para inserir um valor na Árvore Binária de Busca (BST)
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarNode(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    // Se o valor for igual, não faz nada (o problema diz que são distintos)
    
    return raiz;
}

// Estrutura para a Fila (Queue) necessária para o BFS
typedef struct {
    Node* itens[600]; // Tamanho suficiente para N <= 500
    int inicio;
    int fim;
} Fila;

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
}

void enfileirar(Fila* f, Node* node) {
    f->itens[f->fim] = node;
    f->fim++;
}

Node* desenfileirar(Fila* f) {
    if (f->inicio == f->fim) return NULL;
    Node* node = f->itens[f->inicio];
    f->inicio++;
    return node;
}

int filaVazia(Fila* f) {
    return f->inicio == f->fim;
}

// Função para liberar a memória da árvore (limpeza pós-teste)
void liberarArvore(Node* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// Função para realizar o percurso por nível (BFS)
void percursoPorNivel(Node* raiz) {
    if (raiz == NULL) return;

    Fila fila;
    inicializarFila(&fila);
    enfileirar(&fila, raiz);

    int primeiro = 1; // Flag para controlar o espaço antes do número

    while (!filaVazia(&fila)) {
        Node* atual = desenfileirar(&fila);

        if (!primeiro) {
            printf(" ");
        }
        printf("%d", atual->valor);
        primeiro = 0;

        // Importante: Enfileirar filho da esquerda, depois da direita
        if (atual->esquerda != NULL) {
            enfileirar(&fila, atual->esquerda);
        }
        if (atual->direita != NULL) {
            enfileirar(&fila, atual->direita);
        }
    }
    printf("\n"); // Quebra de linha ao final da lista de números
}

int main() {
    int C, N, valor, i, caso = 1;

    scanf("%d", &C);

    while (C--) {
        scanf("%d", &N);
        
        Node* raiz = NULL;

        for (i = 0; i < N; i++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", caso++);
        percursoPorNivel(raiz);
        printf("\n"); // Linha em branco exigida após cada caso de teste

        liberarArvore(raiz);
    }

    return 0;
}
