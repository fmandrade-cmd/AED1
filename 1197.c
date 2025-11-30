/******************************************************************************
 * Disciplina: Algoritmos e Estruturas de Dados I
 * Período:    2º Semestre - 2º Termo
 * Projeto:    Deslocamento de Partícula
 *
 * Aluno(a):   Fábio Miguel de Andrade
 * Matrícula:  176.482
 * Data:       19/10/2025
 *
 * Problema: Calcular deslocamento de partícula com aceleração constante
 * 
 * Fórmulas da Cinemática:
 * v = v0 + a*t          (velocidade)
 * s = v0*t + (a*t²)/2   (deslocamento)
 ******************************************************************************/
#include <stdio.h>

int main() {
    int v, t;

    while (scanf("%d %d", &v, &t) == 2) {
        
        int deslocamento = v * 2 * t;
        
        printf("%d\n", deslocamento);
    }

    return 0;
}
