#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fila.h"

struct aluno {
	int matricula;
	char nome[32];
};

struct fila {
	Aluno *vec;
	size_t size, capacity;
	int front, rear;
};

Fila* criarFila() {
	Fila *f = (Fila *) malloc(sizeof(Fila));
	if (f) {
		f->front = 0;
		f->rear = 0;
		f->capacity = 8;

		f->vec = (Aluno *) malloc(sizeof(Aluno) * f->capacity);
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

void insertFila(Fila *f, Aluno *a) { // O(1)
	if (!f || f->size == f->capacity)
		return;

	f->vec[f->rear] = *a;		
	f->rear = (f->rear + 1) % f->capacity;
	f->size++;
}

int popFila(Fila *f) { // O(1)
	if (!f || f->size == 0)
		return -1; 

	Aluno aluno = f->vec[f->front];
	int val = aluno.matricula;
	f->front = (f->front + 1) % f->capacity;
	f->size--;

	return val;
}

void printFila(Fila *f) {
	if (!f)
		return;

	for (int i = 0; i < f->size; i++)
		printf("Nome: %s - Matrícula: %d\n", f->vec[(f->front + i) % f->capacity].nome, f->vec[(f->front + i) % f->capacity].matricula);
	printf("\n");
}

Aluno* criaAluno(int matricula, char nome[]) {
	Aluno *a = malloc(sizeof(Aluno));
	a->matricula = matricula;
	strcpy(a->nome, nome);

	return a;
} 
