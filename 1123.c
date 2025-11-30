#include <stdio.h>
#include <stdlib.h>

#define MAX_N 255
#define INF 100000000

int adj[MAX_N][MAX_N];
int dist[MAX_N];
int visitado[MAX_N];

void resolver(int N, int M, int C, int K) {
    int i, j, u, v, p;

    // 1. Inicialização
    for (i = 0; i < N; i++) {
        dist[i] = INF;
        visitado[i] = 0;
        for (j = 0; j < N; j++) {
            adj[i][j] = INF;
        }
    }

    // 2. Leitura das arestas
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &u, &v, &p);
        // Grafo não direcionado (mão dupla)
        if (p < adj[u][v]) { // Garante pegar o menor custo se houver múltiplas entradas (embora o problema diga que não há)
            adj[u][v] = p;
            adj[v][u] = p;
        }
    }

    // 3. Dijkstra (Versão O(N^2) sem Heap)
    dist[K] = 0;

    for (i = 0; i < N; i++) {
        int u = -1;
        int min_dist = INF;

        // Encontra o nó não visitado com a menor distância
        for (j = 0; j < N; j++) {
            if (!visitado[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        // Se não alcançamos nenhum nó novo ou o nó mais próximo é infinito
        if (u == -1 || dist[u] == INF) break;

        visitado[u] = 1;

        // --- PONTO CRUCIAL DO PROBLEMA ---
        // Se chegamos a uma cidade da Rota de Serviço (0 até C-1),
        // NÃO expandimos para seus vizinhos. O caminho a partir daqui é fixo.
        if (u < C) continue;

        // Relaxamento dos vizinhos
        for (v = 0; v < N; v++) {
            if (adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    // 4. Cálculo final combinando (Caminho até rota) + (Custo fixo da rota)
    int resposta = dist[C - 1]; // Custo se chegarmos direto ao destino (se possível)
    int custo_rota_acumulado = 0;

    // Percorremos a rota de trás para frente (de C-2 até 0)
    // O destino é C-1, então começamos olhando o custo para chegar em C-2 e ir para C-1
    for (i = C - 2; i >= 0; i--) {
        // Custo da estrada fixa da rota (i -> i+1)
        if (adj[i][i+1] != INF) {
            custo_rota_acumulado += adj[i][i+1];
        } else {
            // Se a estrada da rota não existe (teoricamente impossível pela descrição), interrompe
            custo_rota_acumulado = INF; 
        }
        
        // Verifica o custo total entrando na rota pela cidade 'i'
        if (dist[i] != INF && custo_rota_acumulado < INF) {
            int custo_total = dist[i] + custo_rota_acumulado;
            if (custo_total < resposta) {
                resposta = custo_total;
            }
        }
    }

    printf("%d\n", resposta);
}

int main() {
    int N, M, C, K;

    // Loop de leitura até encontrar a linha de zeros (0 0 0 0)
    while (scanf("%d %d %d %d", &N, &M, &C, &K) && (N || M || C || K)) {
        resolver(N, M, C, K);
    }

    return 0;
}
