/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Detecção de Ciclos em Grafos
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Detectar ciclos em grafo direcionado (dependências de documentos)
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10001

// Estrutura para Lista de Adjacência (usando vetor de vetores)
typedef struct {
    int *vizinhos;
    int numVizinhos;
    int capacidade;
} ListaAdj;

typedef struct {
    int numVertices;
    ListaAdj *adj;
} Grafo;

// Inicializa o grafo
Grafo* criarGrafo(int numVertices) {
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->numVertices = numVertices;
    g->adj = (ListaAdj*)malloc((numVertices + 1) * sizeof(ListaAdj));
    
    for (int i = 0; i <= numVertices; i++) {
        g->adj[i].vizinhos = NULL;
        g->adj[i].numVizinhos = 0;
        g->adj[i].capacidade = 0;
    }
    
    return g;
}

// Adiciona aresta direcionada (A -> B)
void adicionarAresta(Grafo *g, int origem, int destino) {
    ListaAdj *lista = &g->adj[origem];
    
    // Verifica se precisa aumentar a capacidade
    if (lista->numVizinhos >= lista->capacidade) {
        int novaCapacidade = lista->capacidade == 0 ? 4 : lista->capacidade * 2;
        lista->vizinhos = (int*)realloc(lista->vizinhos, novaCapacidade * sizeof(int));
        lista->capacidade = novaCapacidade;
    }
    
    lista->vizinhos[lista->numVizinhos++] = destino;
}

// DFS para detectar ciclo
// Estados: 0 = não visitado, 1 = visitando (pilha de recursão), 2 = visitado
int DFS_temCiclo(Grafo *g, int v, int *estado) {
    estado[v] = 1;  // Marca como "visitando"
    
    ListaAdj *lista = &g->adj[v];
    
    // Verifica todos os vizinhos
    for (int i = 0; i < lista->numVizinhos; i++) {
        int vizinho = lista->vizinhos[i];
        
        if (estado[vizinho] == 1) {
            // Encontrou um vértice na pilha de recursão = CICLO!
            return 1;
        }
        
        if (estado[vizinho] == 0) {
            // Vértice não visitado, continua DFS
            if (DFS_temCiclo(g, vizinho, estado)) {
                return 1;
            }
        }
    }
    
    estado[v] = 2;  // Marca como "visitado"
    return 0;
}

// Verifica se existe ciclo no grafo
int detectarCiclo(Grafo *g) {
    int *estado = (int*)calloc(g->numVertices + 1, sizeof(int));
    
    if (estado == NULL) {
        return 0;
    }
    
    // Testa DFS a partir de cada vértice não visitado
    for (int i = 1; i <= g->numVertices; i++) {
        if (estado[i] == 0) {
            if (DFS_temCiclo(g, i, estado)) {
                free(estado);
                return 1;  // Encontrou ciclo
            }
        }
    }
    
    free(estado);
    return 0;  // Não encontrou ciclo
}

// Libera a memória do grafo
void liberarGrafo(Grafo *g) {
    for (int i = 0; i <= g->numVertices; i++) {
        if (g->adj[i].vizinhos != NULL) {
            free(g->adj[i].vizinhos);
        }
    }
    free(g->adj);
    free(g);
}

int main() {
    int T, N, M, A, B;
    
    scanf("%d", &T);
    
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &N, &M);
        
        Grafo *grafo = criarGrafo(N);
        
        // Lê as dependências e constrói o grafo
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &A, &B);
            adicionarAresta(grafo, A, B);  // A depende de B: aresta A -> B
        }
        
        // Detecta ciclo
        if (detectarCiclo(grafo)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        
        liberarGrafo(grafo);
    }
    
    return 0;
}
