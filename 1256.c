#include <stdio.h>
#include <stdlib.h>

// Definição do nó da lista encadeada
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        exit(1); // Erro de alocação
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Função para inserir um valor no final da lista
// Recebe o endereço do ponteiro da cabeça da lista
void inserir(No **cabeca, int valor) {
    No *novo = criarNo(valor);
    
    // Se a lista estiver vazia, o novo nó é a cabeça
    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        // Percorre até o último nó
        No *temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
}

// Função para liberar a memória de uma lista
void liberarLista(No *cabeca) {
    No *atual = cabeca;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

void resolver() {
    int N; // Quantidade de casos de teste
    scanf("%d", &N);

    while (N--) {
        int M, C;
        // M = tamanho da tabela (endereços base)
        // C = quantidade de chaves
        scanf("%d %d", &M, &C);

        // Tabela Hash: vetor de ponteiros para nós
        // Como M <= 100, podemos alocar estaticamente ou dinamicamente
        No* tabela[105]; 

        // Inicializa a tabela com NULL
        for (int i = 0; i < M; i++) {
            tabela[i] = NULL;
        }

        // Leitura e inserção das chaves
        for (int i = 0; i < C; i++) {
            int chave;
            scanf("%d", &chave);
            
            // Função de dispersão: h(x) = x mod M
            int indice = chave % M;
            
            // Insere na lista encadeada correspondente ao índice
            inserir(&tabela[indice], chave);
        }

        // Impressão da tabela
        for (int i = 0; i < M; i++) {
            printf("%d -> ", i);
            
            No *atual = tabela[i];
            while (atual != NULL) {
                printf("%d -> ", atual->valor);
                atual = atual->proximo;
            }
            
            printf("\\\n"); // Imprime a barra invertida no final
        }

        // Libera a memória alocada para este caso de teste
        for (int i = 0; i < M; i++) {
            liberarLista(tabela[i]);
        }

        // Se houver mais casos de teste, imprime uma linha em branco separadora
        if (N > 0) {
            printf("\n");
        }
    }
}

int main() {
    resolver();
    return 0;
}
