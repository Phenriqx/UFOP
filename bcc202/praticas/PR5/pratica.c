#include <stdio.h>

#include "aluno.h"

int main() {
	int n;
	scanf("%d", &n);
	Pecas* pecas = criaPecas(n);

	lerInput(pecas);

	ordenaPecas(pecas);

	freePecas(&pecas);
	return 0;
}
