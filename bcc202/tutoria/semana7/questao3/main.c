#include "lista.h"

int main() {
	Lista* lista = criaLista();

	inserirFim(lista, 1);
	inserirFim(lista, 12);
	inserirFim(lista, 3);
	inserirFim(lista, 20);
	inserirFim(lista, 5);
	inserirFim(lista, 11);
	inserirFim(lista, 23);
	inserirFim(lista, 7);
	inserirFim(lista, 32);

	printLista(lista);

	removeMaior(lista);
	printLista(lista);

	freeLista(&lista);
	return 0;
}
