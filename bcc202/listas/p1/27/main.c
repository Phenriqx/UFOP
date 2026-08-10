#include <stdio.h>

#define N 3

int somaMatrizRec(int mat[N][N], int row, int col);

int main() {
    int mat[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = 1;

    int soma = somaMatrizRec(mat, N - 1, N - 1);
    printf("Soma dos elementos da matriz: %d\n", soma);

    return 0;
}

int somaMatrizRec(int mat[N][N], int row, int col) {
    if (row < 0)
        return 0;

    if (col < 0)
        return somaMatrizRec(mat, row - 1, N - 1);

    return mat[row][col] + somaMatrizRec(mat, row, col - 1);
}