/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Componentes Conexos de Grafos
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Identificar e listar componentes conexos de um grafo não direcionado
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 26

// Estrutura do Grafo com Matriz de Adjacências
typedef struct {
    int numVertices;
    int matrizAdj[MAX_VERTICES][MAX_VERTICES];
    int visitado[MAX_VERTICES];
} Grafo;

// Inicializa o grafo
void inicializarGrafo(Grafo *g, int numVertices) {
    g->numVertices = numVertices;
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->visitado[i] = 0;
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->matrizAdj[i][j] = 0;
        }
    }
}

// Adiciona aresta não direcionada
void adicionarAresta(Grafo *g, char u, char v) {
    int i = u - 'a';
    int j = v - 'a';
    g->matrizAdj[i][j] = 1;
    g->matrizAdj[j][i] = 1;  // Grafo não direcionado
}

// DFS para encontrar todos os vértices de um componente conexo
void DFS(Grafo *g, int v, int componente[], int *tamanho) {
    g->visitado[v] = 1;
    componente[(*tamanho)++] = v;
    
    // Explora todos os vizinhos
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matrizAdj[v][i] == 1 && !g->visitado[i]) {
            DFS(g, i, componente, tamanho);
        }
    }
}

// Função de comparação para qsort
int compararInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Encontra e imprime todos os componentes conexos
void encontrarComponentes(Grafo *g, int casoTeste) {
    int numComponentes = 0;
    
    printf("Case #%d:\n", casoTeste);
    
    // Para cada vértice não visitado, inicia uma DFS
    for (int i = 0; i < g->numVertices; i++) {
        if (!g->visitado[i]) {
            int componente[MAX_VERTICES];
            int tamanho = 0;
            
            // DFS para encontrar todos os vértices do componente
            DFS(g, i, componente, &tamanho);
            
            // Ordena os vértices do componente
            qsort(componente, tamanho, sizeof(int), compararInt);
            
            // Imprime os vértices do componente
            for (int j = 0; j < tamanho; j++) {
                printf("%c,", 'a' + componente[j]);
            }
            printf("\n");
            
            numComponentes++;
        }
    }
    
    // Imprime a quantidade de componentes
    printf("%d connected component", numComponentes);
    if (numComponentes >= 1) {
        printf("s");
    }
    printf("\n\n");
}

int main() {
    int N, V, E;
    char u, v;
    
    scanf("%d", &N);
    
    for (int casoTeste = 1; casoTeste <= N; casoTeste++) {
        scanf("%d %d", &V, &E);
        
        Grafo grafo;
        inicializarGrafo(&grafo, V);
        
        // Lê as arestas
        for (int i = 0; i < E; i++) {
            scanf(" %c %c", &u, &v);
            adicionarAresta(&grafo, u, v);
        }
        
        // Encontra e imprime os componentes conexos
        encontrarComponentes(&grafo, casoTeste);
    }
    
    return 0;
}
