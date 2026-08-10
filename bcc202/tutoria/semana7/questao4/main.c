#include <stdio.h>

#include "fila.h"

int main() {
	Fila *f = criaFila();

	for (int i = 1; i <= 5; i++)
		filaEnfileira(f, i);

	printFila(f);

	int pop = filaDesenfileira(f);
	printf("valor pop: %d\n", pop);

	printFila(f);

	destroiFila(&f);
	return 0;
}
