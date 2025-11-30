/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Colorir Cenários de Jogo
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Contar regiões brancas conectadas usando BFS/DFS
 * 
 * Conceito: Flood Fill - mesmo conceito do "balde de tinta" de programas de edição
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1025

char mapa[MAX][MAX];
int visitado[MAX][MAX];
int N, M;

// Direções: cima, baixo, esquerda, direita
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Estrutura para a fila (BFS)
typedef struct {
    int x, y;
} Ponto;

Ponto fila[MAX * MAX];
int inicio, fim;

// Verifica se a posição é válida
int valido(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

// BFS para marcar toda a região branca conectada
void BFS(int startX, int startY) {
    inicio = 0;
    fim = 0;
    
    // Adiciona o ponto inicial na fila
    fila[fim].x = startX;
    fila[fim].y = startY;
    fim++;
    visitado[startX][startY] = 1;
    
    while (inicio < fim) {
        // Remove da fila
        Ponto atual = fila[inicio++];
        
        // Explora os 4 vizinhos (cima, baixo, esquerda, direita)
        for (int i = 0; i < 4; i++) {
            int novoX = atual.x + dx[i];
            int novoY = atual.y + dy[i];
            
            // Se é válido, branco e não visitado
            if (valido(novoX, novoY) && 
                mapa[novoX][novoY] == '.' && 
                !visitado[novoX][novoY]) {
                
                visitado[novoX][novoY] = 1;
                fila[fim].x = novoX;
                fila[fim].y = novoY;
                fim++;
            }
        }
    }
}

// Alternativa: DFS recursiva (mais simples, mas pode dar stack overflow em casos grandes)
void DFS(int x, int y) {
    // Marca como visitado
    visitado[x][y] = 1;
    
    // Explora os 4 vizinhos
    for (int i = 0; i < 4; i++) {
        int novoX = x + dx[i];
        int novoY = y + dy[i];
        
        if (valido(novoX, novoY) && 
            mapa[novoX][novoY] == '.' && 
            !visitado[novoX][novoY]) {
            
            DFS(novoX, novoY);
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    // Lê o mapa
    for (int i = 0; i < N; i++) {
        scanf("%s", mapa[i]);
    }
    
    // Inicializa a matriz de visitados
    memset(visitado, 0, sizeof(visitado));
    
    int cliques = 0;
    
    // Percorre toda a imagem
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Se encontrou um pixel branco não visitado
            if (mapa[i][j] == '.' && !visitado[i][j]) {
                // Conta um clique para esta região
                cliques++;
                
                // Marca toda a região conectada como visitada
                BFS(i, j);
                // Ou use DFS: DFS(i, j);
            }
        }
    }
    
    printf("%d\n", cliques);
    
    return 0;
}
