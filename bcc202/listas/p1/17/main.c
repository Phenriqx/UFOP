#include <stdio.h>

int main() {
	int mat[3][4];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = i + j;

		// 0 1 2 3
		// 1 2 3 4
		// 2 3 4 5

	
}

int calculaSemana(int mat[3][4], int row, int col) {
	if (row == 2)
		return 0;

	return mat[row][col] + calculaSemana(mat, row + 1, col);
}

int calculaMes(int mat[3][4], int row, int col) {
	if (col == 3)
		return 0;

	return mat[row][col] + calculaMes(mat, row, col + 1);
}

int calculaAno(int mat[3][4], int row, int col) {
	if (row == 2)
		return 0;

	if (col == 2)
			return 
}
