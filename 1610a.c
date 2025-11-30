/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Detecção de Ciclos em Grafos
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Detectar ciclos em grafo direcionado usando Matriz de Adjacências
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Estrutura do Grafo com Matriz de Adjacências
typedef struct {
    int numVertices;
    int **matrizAdj;
} Grafo;

// Cria e inicializa a matriz de adjacências
int** criarMatrizAdj(int numVertices) {
    int **matriz = (int**)malloc((numVertices + 1) * sizeof(int*));
    
    for (int i = 0; i <= numVertices; i++) {
        matriz[i] = (int*)calloc((numVertices + 1), sizeof(int));
    }
    
    return matriz;
}

// Libera a matriz de adjacências
void liberarMatrizAdj(int **matriz, int numVertices) {
    for (int i = 0; i <= numVertices; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Inicializa o grafo
Grafo* criarGrafo(int numVertices) {
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->numVertices = numVertices;
    g->matrizAdj = criarMatrizAdj(numVertices);
    return g;
}

// Adiciona aresta direcionada (A -> B)
void adicionarAresta(Grafo *g, int origem, int destino) {
    g->matrizAdj[origem][destino] = 1;
}

// DFS para detectar ciclo
// Estados: 0 = não visitado, 1 = visitando (pilha de recursão), 2 = visitado
int DFS_temCiclo(Grafo *g, int v, int *estado) {
    estado[v] = 1;  // Marca como "visitando"
    
    // Verifica todos os possíveis vizinhos
    for (int i = 1; i <= g->numVertices; i++) {
        // Se existe aresta v -> i
        if (g->matrizAdj[v][i] == 1) {
            if (estado[i] == 1) {
                // Encontrou um vértice na pilha de recursão = CICLO!
                return 1;
            }
            
            if (estado[i] == 0) {
                // Vértice não visitado, continua DFS
                if (DFS_temCiclo(g, i, estado)) {
                    return 1;
                }
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
    liberarMatrizAdj(g->matrizAdj, g->numVertices);
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
