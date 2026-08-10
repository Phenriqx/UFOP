#include <stdio.h>
#include "fila.h"

int main() {
	Queue* f1 = createQueue();
	for (int i = 0; i < 3; i++)
		appendQueue(f1, i + 1);

	printQueue(f1);

	filhaEspelho(f1);

	freeQueue(&f1);
	return 0;
}
