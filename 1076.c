/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Exercícios Que compõesm a nota
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100 // Tamanho máximo de vértices (segurança)

// Estrutura de um Nó para a Lista de Adjacência
typedef struct No {
    int destino;
    struct No* proximo;
} No;

// Variáveis globais para o Grafo
No* listaAdj[MAX_V];
int movimentos; // Contador global de movimentos

// Função para criar um novo nó na lista
No* criarNo(int destino) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}

// Verifica se a aresta u -> v já existe na lista de u
int existeAresta(int u, int v) {
    No* temp = listaAdj[u];
    while (temp != NULL) {
        if (temp->destino == v) return 1; // Verdadeiro
        temp = temp->proximo;
    }
    return 0; // Falso
}

// Adiciona aresta não direcionada (u <-> v)
void adicionarAresta(int u, int v) {
    // Como o problema diz que arestas repetidas são opcionais,
    // nós só adicionamos se ela AINDA NÃO existir.
    if (!existeAresta(u, v)) {
        // Adiciona v na lista de u
        No* novo = criarNo(v);
        novo->proximo = listaAdj[u];
        listaAdj[u] = novo;

        // Adiciona u na lista de v (grafo não direcionado)
        novo = criarNo(u);
        novo->proximo = listaAdj[v];
        listaAdj[v] = novo;
    }
}

// Função para limpar a memória do grafo
void liberarGrafo(int V) {
    for (int i = 0; i < V; i++) {
        No* temp = listaAdj[i];
        while (temp != NULL) {
            No* apagar = temp;
            temp = temp->proximo;
            free(apagar);
        }
        listaAdj[i] = NULL;
    }
}

// Busca em Profundidade (DFS) para contar os movimentos
// u: vértice atual
// pai: vértice de onde viemos (para não voltar imediatamente)
void dfs(int u, int pai) {
    No* vizinho = listaAdj[u];
    
    while (vizinho != NULL) {
        int v = vizinho->destino;
        
        // Se o vizinho não for o "pai" (de onde acabamos de vir), avançamos
        if (v != pai) {
            movimentos++; // Movimento de IDA
            dfs(v, u);    // Recursão para o vizinho
            movimentos++; // Movimento de VOLTA (backtracking)
        }
        
        vizinho = vizinho->proximo;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int inicio;
        scanf("%d", &inicio); // O ponto de partida do desenho

        int V, A;
        scanf("%d %d", &V, &A); // Vértices e Arestas

        // Inicializa o grafo para este caso de teste
        // (Assume-se que os vértices são numerados de 0 a V, ou usamos MAX_V para garantir)
        for(int i = 0; i < MAX_V; i++) listaAdj[i] = NULL;
        movimentos = 0;

        // Leitura das arestas
        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adicionarAresta(u, v);
        }

        // Executa a DFS a partir do nó de início dado no problema.
        // O pai inicial é -1 pois o nó de início não tem pai.
        dfs(inicio, -1);

        printf("%d\n", movimentos);

        // Limpa a memória
        liberarGrafo(MAX_V);
    }

    return 0;
}
