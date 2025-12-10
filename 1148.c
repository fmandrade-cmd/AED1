#include <stdio.h>
#include <string.h>

#define INF 1000000000
#define MAX_N 505
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int dist[MAX_N][MAX_N];
int n, e;

// Algoritmo de Tarjan para encontrar componentes fortemente conexos
int low[MAX_N], disc[MAX_N], stackMember[MAX_N];
int st[MAX_N], top = -1;
int sccId[MAX_N], sccCount = 0;
int timer = 0;
int adj[MAX_N][MAX_N];

void tarjanDFS(int u) {
    disc[u] = low[u] = ++timer;
    st[++top] = u;
    stackMember[u] = 1;
    
    for (int v = 1; v <= n; v++) {
        if (adj[u][v]) {
            if (disc[v] == -1) {
                tarjanDFS(v);
                low[u] = MIN(low[u], low[v]);
            } else if (stackMember[v]) {
                low[u] = MIN(low[u], disc[v]);
            }
        }
    }
    
    if (low[u] == disc[u]) {
        while (1) {
            int v = st[top--];
            stackMember[v] = 0;
            sccId[v] = sccCount;
            if (v == u) break;
        }
        sccCount++;
    }
}

void findSCC() {
    for (int i = 1; i <= n; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = 0;
        sccId[i] = -1;
    }
    
    timer = 0;
    sccCount = 0;
    top = -1;
    
    for (int i = 1; i <= n; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i);
        }
    }
}

int main() {
    while (1) {
        scanf("%d %d", &n, &e);
        if (n == 0 && e == 0) break;
        
        // Inicializar
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                adj[i][j] = 0;
                if (i == j) {
                    dist[i][j] = 0;
                } else {
                    dist[i][j] = INF;
                }
            }
        }
        
        // Ler acordos
        for (int i = 0; i < e; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            adj[x][y] = 1;
            dist[x][y] = h;
        }
        
        // Encontrar componentes fortemente conexos (países)
        findSCC();
        
        // Cidades no mesmo componente têm comunicação instantânea
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && sccId[i] == sccId[j]) {
                    dist[i][j] = 0;
                }
            }
        }
        
        // Floyd-Warshall para caminhos mínimos
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        
        // Processar consultas
        int k;
        scanf("%d", &k);
        
        for (int i = 0; i < k; i++) {
            int o, d;
            scanf("%d %d", &o, &d);
            
            if (dist[o][d] == INF) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", dist[o][d]);
            }
        }
        
        printf("\n");
    }
    
    return 0;
}
