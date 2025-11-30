#include <stdio.h>
#include <stdlib.h>

#define MAX_CIDADES 40005
#define MAX_ESTRADAS 50005

// Estrutura para representar uma estrada (aresta do grafo)
typedef struct {
    int u;      // Cidade de origem
    int v;      // Cidade de destino
    int peso;   // Distância
} Aresta;

// Variáveis globais para armazenar o grafo e a estrutura Union-Find
Aresta arestas[MAX_ESTRADAS];
int pai[MAX_CIDADES];

// Função de comparação para o qsort (ordena as arestas pelo peso)
int comparar(const void *a, const void *b) {
    Aresta *arestaA = (Aresta *)a;
    Aresta *arestaB = (Aresta *)b;
    return arestaA->peso - arestaB->peso;
}

// --- Funções do Union-Find (Conjuntos Disjuntos) ---

// Encontra o representante (raiz) do conjunto de uma cidade 'i'
// Utiliza compressão de caminho para otimizar buscas futuras
int find(int i) {
    if (pai[i] == i)
        return i;
    return pai[i] = find(pai[i]);
}

// Une os conjuntos de duas cidades 'i' e 'j'
void union_sets(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);
    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j;
    }
}

// --- Função Principal ---

int main() {
    int M, N; // M = Cidades, N = Caminhos

    // Lê os casos de teste até que M e N sejam 0
    while (scanf("%d %d", &M, &N) && (M != 0 || N != 0)) {
        
        // 1. Leitura das arestas
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].peso);
        }

        // 2. Ordenação das arestas (passo crucial do Kruskal)
        qsort(arestas, N, sizeof(Aresta), comparar);

        // 3. Inicialização do Union-Find
        // Cada cidade começa sendo pai de si mesma (conjunto isolado)
        for (int i = 0; i < M; i++) {
            pai[i] = i;
        }

        int custo_total = 0;
        
        // 4. Construção da Árvore Geradora Mínima (MST)
        for (int i = 0; i < N; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;

            // Se as cidades u e v ainda não estão conectadas
            if (find(u) != find(v)) {
                union_sets(u, v);          // Conecta os componentes
                custo_total += arestas[i].peso; // Soma a distância
            }
        }

        printf("%d\n", custo_total);
    }

    return 0;
}
