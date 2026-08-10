#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

struct fila {
	int *vec;
	size_t size, capacity;
	int front, rear;
};

Fila* criaFila() {
	Fila *f = (Fila *) malloc(sizeof(Fila));
	if (f) {
		f->capacity = 8;
		f->size = 0;
		f->front = 0;
		f->rear = 0;
		f->vec = (int *) malloc(sizeof(int) * f->capacity);
		if (!f->vec) {
			free(f);
			return NULL;
		}
	}

	return f;
}

void destroiFila(Fila **f) {
	if (*f) 
		free((*f)->vec);

	free(*f);
	*f = NULL;
}

void filaEnfileira(Fila *f, int val) {
	if (!f) 
		return;

	f->vec[f->rear] = val;
	f->rear = (f->rear + 1) % f->capacity;
	f->size++;
}

int filaDesenfileira(Fila *f) {
	if (!f || f->size == 0)
		return -1;

	int pop = f->vec[f->front];
	f->front = (f->front + 1) % f->capacity;
	f->size--;
	
	return pop;
}

void printFila(Fila* f) { 
	if (!f)
		return;

	printf("[ ");
	int curr_index;
	for (int i = 0; i < f->size; i++) {
		curr_index = (f->front + i) % f->capacity;
		printf("%d ", f->vec[curr_index]);
	}

	printf("]\n");
}
