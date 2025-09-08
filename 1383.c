#include <stdio.h>

int verifica_linha(int mat[9][9], int l) {
    int seen[10] = {0};
    for (int j = 0; j < 9; j++) {
        int v = mat[l][j];
        if (seen[v]) return 0;
        seen[v] = 1;
    }
    return 1;
}

int verifica_coluna(int mat[9][9], int c) {
    int seen[10] = {0};
    for (int i = 0; i < 9; i++) {
        int v = mat[i][c];
        if (seen[v]) return 0;
        seen[v] = 1;
    }
    return 1;
}

int verifica_bloco(int mat[9][9], int lin, int col) {
    int seen[10] = {0};
    for (int i = lin; i < lin + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            int v = mat[i][j];
            if (seen[v]) return 0;
            seen[v] = 1;
        }
    }
    return 1;
}

int main() {
    int n, mat[9][9];

    scanf("%d", &n);

    for (int inst = 1; inst <= n; inst++) {
        // Leitura da matriz
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                scanf("%d", &mat[i][j]);

        int valido = 1;

        // Verifica linhas e colunas
        for (int i = 0; i < 9 && valido; i++) {
            if (!verifica_linha(mat, i) || !verifica_coluna(mat, i))
                valido = 0;
        }

        // Verifica blocos 3x3
        for (int i = 0; i < 9 && valido; i += 3) {
            for (int j = 0; j < 9 && valido; j += 3) {
                if (!verifica_bloco(mat, i, j))
                    valido = 0;
            }
        }

        printf("Instancia %d\n", inst);
        if (valido)
            printf("SIM\n");
        else
            printf("NAO\n");
        printf("\n");
    }

    return 0;
}
