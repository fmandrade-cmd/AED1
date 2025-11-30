#include <stdio.h>
#include <stdlib.h>

#define MAX_C 10005       // Máximo de cidades
#define MAX_V 50005       // Máximo de estradas
#define MAX_EDGES 100010  // 2x estradas (bidirecional)
#define INF 1000000000

// --- ESTRUTURAS PARA O GRAFO (Lista de Adjacência) ---
typedef struct {
    int to;
    int weight;
    int next; // Índice da próxima aresta na lista ligada do nó
} Edge;

Edge edges[MAX_EDGES];
int head[MAX_C]; // head[u] aponta para a primeira aresta de u
int edge_cnt;

void init_graph(int n) {
    edge_cnt = 0;
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
    }
}

void add_edge(int u, int v, int w) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].weight = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

// --- ESTRUTURA PARA O HEAP (Fila de Prioridade) ---
typedef struct {
    int dist; // Custo acumulado
    int u;    // Cidade atual
    int p;    // Paridade (0 = par, 1 = ímpar)
} Node;

Node heap[MAX_EDGES * 4]; // Tamanho seguro para o heap
int heap_size;

void heap_push(int d, int u, int p) {
    int i = heap_size++;
    while (i > 0) {
        int p_idx = (i - 1) / 2;
        if (heap[p_idx].dist <= d) break;
        heap[i] = heap[p_idx];
        i = p_idx;
    }
    heap[i].dist = d;
    heap[i].u = u;
    heap[i].p = p;
}

Node heap_pop() {
    Node ret = heap[0];
    Node x = heap[--heap_size];
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int child = i * 2 + 1;
        if (child + 1 < heap_size && heap[child + 1].dist < heap[child].dist) {
            child++;
        }
        if (heap[child].dist >= x.dist) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = x;
    return ret;
}

// --- VARIÁVEIS DO DIJKSTRA ---
// dist[cidade][0] = menor custo par
// dist[cidade][1] = menor custo ímpar
int dist[MAX_C][2]; 

void resolver(int C, int V) {
    int i;
    
    // Inicialização do grafo e distâncias
    init_graph(C);
    for (i = 0; i <= C; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    // Leitura das arestas
    for (i = 0; i < V; i++) {
        int u, v, g;
        if (scanf("%d %d %d", &u, &v, &g) != 3) break;
        add_edge(u, v, g);
        add_edge(v, u, g); // Bidirecional
    }

    // Dijkstra
    heap_size = 0;
    
    // Começamos na cidade 1, custo 0, paridade 0 (0 arestas é par)
    dist[1][0] = 0;
    heap_push(0, 1, 0);

    while (heap_size > 0) {
        Node atual = heap_pop();
        int d = atual.dist;
        int u = atual.u;
        int p = atual.p;

        // Se encontramos um caminho pior do que já temos, ignoramos
        if (d > dist[u][p]) continue;

        // Itera sobre os vizinhos usando a lista de adjacência
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int peso = edges[e].weight;
            int next_p = 1 - p; // Inverte paridade: 0->1, 1->0

            if (dist[u][p] + peso < dist[v][next_p]) {
                dist[v][next_p] = dist[u][p] + peso;
                heap_push(dist[v][next_p], v, next_p);
            }
        }
    }

    // O destino é a cidade C, e queremos paridade 0 (par)
    int ans = dist[C][0];
    
    if (ans == INF) printf("-1\n");
    else printf("%d\n", ans);
}

int main() {
    int C, V;
    // Loop para ler múltiplos casos de teste até EOF
    while (scanf("%d %d", &C, &V) != EOF) {
        resolver(C, V);
    }
    return 0;
}
