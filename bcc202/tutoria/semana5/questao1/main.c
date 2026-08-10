#include <stdio.h>

#include "pilha_pont.h"
#include "pilha_vec.h"

int main() {
	Pilha *p = criaPilha();
	for (int i = 0; i < 5; i++)
		pilhaPush(p, i + 1);

	printPilha(p);
	int pop = pilhaPop(p);
	printf("Valor pop: %d\n", pop);

	printPilha(p);
	freePilha(&p);

	return 0;

	// Pilha* p = criaPilhaPont();

	// printf("Pilha eh vazia: %s\n", pilhaEhVaziaPont(p) ? "Sim" : "Não");
	// for (int i = 0; i < 1; i++) 
	// 	pilhaPushPont(p, i + 1);
	
	// printPilhaPont(p);

	// int pop = pilhaPopPont(p);
	// printf("Valor pop: %d\n", pop);
	
	// printPilhaPont(p);

	// return 0;
}
