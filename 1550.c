/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Aparelho de Pedro - Caminho Mínimo
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Encontrar número mínimo de operações (adicionar 1 ou inverter dígitos)
 *           para transformar número A em B usando BFS
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20000

// Estrutura para representar um estado na fila
typedef struct {
    int numero;
    int passos;
} Estado;

// Fila para BFS
Estado fila[MAX];
int inicio, fim;

// Array para marcar números visitados
int visitado[MAX];

// Função para inverter os dígitos de um número
int inverter(int num) {
    int invertido = 0;
    while (num > 0) {
        invertido = invertido * 10 + (num % 10);
        num /= 10;
    }
    return invertido;
}

// BFS para encontrar o caminho mínimo de A para B
int encontrarCaminhoMinimo(int A, int B) {
    // Limpa o array de visitados
    memset(visitado, 0, sizeof(visitado));
    
    // Inicializa a fila
    inicio = 0;
    fim = 0;
    
    // Adiciona o estado inicial
    fila[fim].numero = A;
    fila[fim].passos = 0;
    fim++;
    visitado[A] = 1;
    
    while (inicio < fim) {
        // Remove da fila
        Estado atual = fila[inicio++];
        
        // Se chegou no destino
        if (atual.numero == B) {
            return atual.passos;
        }
        
        // Operação 1: Adicionar 1
        int proximo1 = atual.numero + 1;
        if (proximo1 < MAX && !visitado[proximo1]) {
            visitado[proximo1] = 1;
            fila[fim].numero = proximo1;
            fila[fim].passos = atual.passos + 1;
            fim++;
        }
        
        // Operação 2: Inverter dígitos
        int proximo2 = inverter(atual.numero);
        if (proximo2 < MAX && !visitado[proximo2]) {
            visitado[proximo2] = 1;
            fila[fim].numero = proximo2;
            fila[fim].passos = atual.passos + 1;
            fim++;
        }
    }
    
    return -1; // Não deveria chegar aqui
}

int main() {
    int T, A, B;
    
    scanf("%d", &T);
    
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &A, &B);
        
        int resultado = encontrarCaminhoMinimo(A, B);
        printf("%d\n", resultado);
    }
    
    return 0;
}
