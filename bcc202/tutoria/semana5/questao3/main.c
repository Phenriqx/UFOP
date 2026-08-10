#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fila.h"

int main() {
	srand(time(NULL));
	Fila* f = criarFila();

	for (int i = 0; i < 5; i++) {
		Item *item = criaItem(i);
		insertFila(f, item);
	} 

	printFila(f);
	int pop = popFila(f);
	printf("Valor pop: %d\n", pop);

	pop = popFila(f);
	printf("Valor pop: %d\n", pop);

	freeFila(&f);
	return 0;
}
