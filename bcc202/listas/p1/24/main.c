#include <stdio.h>
#include <stdlib.h>

int produtoVetor(int *v, int n);
int somaVetor(int *v, int n);
void printVetorInicioFim(int *v, int n);
void printVetorFimInicio(int *v, int n);

int main() {
	int n = 5;
	int *v = malloc(sizeof(int) * n);
	
	for (int i = 0; i < n; i++) 
		v[i] = i + 1;
		// [1, 2, 3, 4, 5]
	
	printVetorInicioFim(v, n - 1);
	
	printf("\n");

	printVetorFimInicio(v, n - 1);
	
	int res = produtoVetor(v, n - 1);	
	printf("\nProduto do vetor: %d\n", res);

	int sum = somaVetor(v, n - 1);
	printf("Soma do vetor: %d\n", sum);

	free(v);
	return 0;
}

int produtoVetor(int *v, int n) {
	if (n < 0)
		return 1;

	return v[n] * produtoVetor(v, n - 1);
}

int somaVetor(int *v, int n) {
	if (n < 0)
		return 0;

	return v[n] + somaVetor(v, n - 1);
}

void printVetorInicioFim(int *v, int n) {
	if (n >= 0) {
		printVetorInicioFim(v, n - 1);
		printf("%d ", v[n]);
	}
}

void printVetorFimInicio(int *v, int n) {
	if (n >= 0) {
		printf("%d ", v[n]);
		printVetorFimInicio(v, n - 1);
	}
}
