#include <stdlib.h>
#include <stdio.h>

#include "pilha_vec.h"

struct pilha {
	int *vet;
	size_t size;
	size_t capacity;
};

Pilha* criaPilha() {
	Pilha *p = (Pilha*) malloc(sizeof(Pilha));
	if (p) {
		p->capacity = 8;
		p->vet = (int *) malloc(sizeof(int) * p->capacity);
		if (!p->vet)
			return NULL;

		p->size = 0;
	}	

	return p;
}

int pilhaEhVazia(Pilha *p) { // O(1)
	return p->size == 0;
}

void pilhaPush(Pilha *p, int val) { // O(1)
	if (!p)
		return;

	p->vet[p->size] = val;
	p->size++;
}

int pilhaPop(Pilha *p) { // O(1)
	if (!p || p->size == 0)
		return -1;

	int pop = p->vet[p->size - 1];
	p->size--;

	return pop;
}

void freePilha(Pilha **p) {
	if (*p) 
		free((*p)->vet);
	
	free(*p);
}

void printPilha(Pilha *p) { // O(n)
	if (!p)
		return;

	for (int i = 0; i < p->size; i++)
		printf("%d ", p->vet[i]);
	printf("\n");
}