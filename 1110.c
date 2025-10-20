#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó (célula) da lista
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Função: Define o ponteiro da Base (Cauda)
// É chamada apenas na primeira inserção (quando nova->proximo é NULL)
void defBase(No *nova, No *base) {
    if (nova->proximo == NULL) {
        base->proximo = nova;
    }
}

// Função: Insere um novo nó no topo (após a cabeça)
void inserir(int y, No *cabeca, No *base) {
    No *nova = (No *)malloc(sizeof(No));
    if (nova == NULL) {
        perror("Erro de alocação de memória.");
        exit(1);
    }
    nova->valor = y;
    nova->proximo = cabeca->proximo;
    cabeca->proximo = nova;

    defBase(nova, base);
}

// Função: Remove o nó do topo, libera a memória e retorna o valor
// Retorna o valor ANTES de liberar a memória
int remover(No *cabeca) {
    if (cabeca->proximo == NULL) return -1; // Lista vazia (caso de segurança)

    No *p = cabeca->proximo;
    int valor_descartado = p->valor;

    cabeca->proximo = p->proximo;
    free(p);

    return valor_descartado;
}

// Função: Move o nó do topo para a base (final da lista)
void moverParaBase(No *cabeca, No *base) {
    No *p = cabeca->proximo; // O nó que será movido

    // 1. Remove 'p' do topo da lista
    cabeca->proximo = p->proximo;

    // 2. Conecta 'p' ao final
    p->proximo = NULL;
    base->proximo->proximo = p;

    // 3. Atualiza a Base (Cauda)
    base->proximo = p;
}

// Função: Executa a simulação (descarte/movimentação) e imprime os resultados
void manipulaCartas(No *cabeca, No *base) {
    printf("Discarded cards: ");
    int primeiro = 1;

    // O loop continua enquanto houver pelo menos 2 cartas (topo != base)
    while (cabeca->proximo != base->proximo) {
        
        // 1. Descartar (Remove o nó do topo e obtém o valor)
        int descartada = remover(cabeca);

        // Lógica de Formatação: Imprime a vírgula antes de todos, exceto o primeiro.
        if (!primeiro) {
            printf(", ");
        }
        printf("%d", descartada);
        primeiro = 0;

        // 2. Mover a próxima carta para a Base
        // O novo topo é cabeca->proximo, que será movido
        // Esta condição de if é uma segurança extra para evitar mover o último nó
        if (cabeca->proximo != base->proximo) {
            moverParaBase(cabeca, base);
        }
    }

    printf("\nRemaining card: %d\n", cabeca->proximo->valor);

    // Gestão de Memória: Libera o último nó remanescente para o próximo caso de teste.
    free(cabeca->proximo);
    cabeca->proximo = NULL;
    base->proximo = NULL;
}

int main() {
    int N;

    // Alocação única dos nós sentinela (Cabeça e Base)
    No *cabeca = (No *)malloc(sizeof(No));
    No *base = (No *)malloc(sizeof(No));

    if (cabeca == NULL || base == NULL) {
        perror("Erro de alocação inicial.");
        return 1;
    }

    // Inicialização dos nós sentinela
    cabeca->valor = -1;
    base->valor = -2;
    cabeca->proximo = NULL;
    base->proximo = NULL;

    // Loop principal: Processa múltiplos casos de teste até N = 0
    while (scanf("%d", &N) == 1 && N != 0) {
        
        if (N < 1 || N > 50) continue; 

        // Caso especial N=1: Nenhuma carta descartada.
        if (N == 1) {
            printf("Discarded cards:\nRemaining card: 1\n");
            continue;
        }

        // 1. Criação da pilha (Lista: 1 -> 2 -> ... -> N)
        for (int i = N; i > 0; i--) {
            inserir(i, cabeca, base);
        }

        // 2. Simulação e Impressão
        manipulaCartas(cabeca, base);
    }

    // Libera os nós sentinela após o loop
    free(cabeca);
    free(base);

    return 0;
}
