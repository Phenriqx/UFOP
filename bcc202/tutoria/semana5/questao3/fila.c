#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

struct item {
	int id;
	int prioridade;
};

struct fila {
	Item *vec;
	size_t size, capacity;
	int front, rear;
};

Fila* criarFila() {
	Fila *f = (Fila *) malloc(sizeof(Fila));
	if (f) {
		f->front = 0;
		f->rear = 0;
		f->capacity = 8;

		f->vec = (Item *) malloc(sizeof(Item) * f->capacity);
		if (!f->vec) {
			free(f);
			return NULL;
		}
	}
	f->size = 0;
	return f;
}

void freeFila(Fila** f) {
	if (*f)
		free((*f)->vec);
	free(*f);
	*f = NULL;
}

void insertFila(Fila *f, Item *i) { // O(1)
	if (!f || f->size == f->capacity)
		return;

	f->vec[f->rear] = *i;		
	f->rear = (f->rear + 1) % f->capacity;
	f->size++;
}

int popFila(Fila *f) { // O(1)
	if (!f || f->size == 0)
		return -1; 

	Item item = f->vec[f->front];
	int val = item.id;
	f->front = (f->front + 1) % f->capacity;
	f->size--;

	if (item.prioridade > 50)
		printf("Prioridade: %d\n", item.prioridade);
	return val;
}

void printFila(Fila *f) {
	if (!f)
		return;

	for (int i = 0; i < f->size; i++)
		printf("Id: %d - Prioridade: %d\n", f->vec[(f->front + i) % f->capacity].id, f->vec[(f->front + i) % f->capacity].prioridade);
	printf("\n");
}

Item* criaItem(int id) {
	Item *i = malloc(sizeof(Item));
	i->id = id;
	i->prioridade = (rand() % 100) + 1;

	return i;
} 
