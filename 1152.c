#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 200005
#define MAX_EDGES 200005

// Estrutura para representar uma estrada (aresta)
typedef struct {
    int u, v;   // Junções conectadas
    int peso;   // Custo (metros/dólares)
} Aresta;

// Variáveis globais para o Union-Find
int pai[MAX_NODES];
Aresta arestas[MAX_EDGES];

// Função de comparação para o qsort (ordenar arestas por peso)
int comparar(const void *a, const void *b) {
    Aresta *arestaA = (Aresta *)a;
    Aresta *arestaB = (Aresta *)b;
    return arestaA->peso - arestaB->peso;
}

// --- Funções do Union-Find ---

// Inicializa cada nó como seu próprio pai
void inicializa_union_find(int n) {
    for (int i = 0; i <= n; i++) {
        pai[i] = i;
    }
}

// Encontra o representante (raiz) do conjunto com compressão de caminho
int find(int i) {
    if (pai[i] == i)
        return i;
    // Compressão de caminho: aponta o nó diretamente para a raiz
    return pai[i] = find(pai[i]);
}

// Une dois conjuntos
void union_sets(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);
    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j;
    }
}

// --- Função Principal ---

void resolver() {
    int m, n; // m = junções, n = estradas

    // Loop de leitura até encontrar m=0 e n=0
    while (scanf("%d %d", &m, &n) && (m != 0 || n != 0)) {
        
        long long custo_total = 0;

        // 1. Leitura das arestas e cálculo do custo total atual
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].peso);
            custo_total += arestas[i].peso;
        }

        // 2. Ordena as arestas pelo peso (menor para maior)
        qsort(arestas, n, sizeof(Aresta), comparar);

        // 3. Inicializa o Union-Find
        inicializa_union_find(m);

        long long custo_mst = 0;
        int arestas_usadas = 0;

        // 4. Algoritmo de Kruskal
        for (int i = 0; i < n; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;

            // Se u e v não estão conectados ainda (não formam ciclo)
            if (find(u) != find(v)) {
                union_sets(u, v);
                custo_mst += arestas[i].peso;
                arestas_usadas++;
            }
        }

        // 5. O resultado é a diferença entre o total e o necessário (MST)
        printf("%lld\n", custo_total - custo_mst);
    }
}

int main() {
    resolver();
    return 0;
}
