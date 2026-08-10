#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

struct queue {
	int *vec;
	size_t size, capacity;
	int front, rear;
};

Queue* createQueue() {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	if (q) {
		q->size = 0;
		q->capacity = 8;
		q->front = 0;
		q->rear = 0;
		q->vec = (int *) malloc(sizeof(int) * q->capacity);
		if (!q->vec) {
			free(q);
			return NULL;
		}
	}

	return q;
}

void freeQueue(Queue **q) {
	if (*q) 
		free((*q)->vec);
	
	free(*q);
	*q = NULL;
}

int sizeQueue(Queue *q) {
	if (q)
		return q->size;

	return -1;
}

void printQueue(Queue *q) {
	if (!q)
		return;

	printf("[ ");
	int curr_index;
	for (int i = 0; i < q->size; i++) {
		curr_index = (q->front + i) % q->capacity;
		printf("%d ", q->vec[curr_index]);
	}

	printf("]\n");
}

void appendQueue(Queue *q, int val) {
	if (!q)
		return;

	q->vec[q->rear] = val;
	q->rear = (q->rear + 1) % q->capacity;
	q->size++;
}

int popQueue(Queue *q) {
	if (!q || sizeQueue(q) == 0)
		return -1;

	int pop = q->vec[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return pop;
}

int isQueueEmpty(Queue* q) {
	return q->size == 0;
}

Queue* filaIntercala(Queue *f1, Queue *f2) {
	int sizef1 = f1->size;
	int sizef2 = f2->size;
	int count = 2;

	Queue* res = createQueue();

	for (int i = 0; i < sizef1 + sizef2; i++) {
		if (count % 2 == 0 && !isQueueEmpty(f1)) 
			appendQueue(res, popQueue(f1));	// f1 = [1 2 3] (pop) -> [2 3]	
		else if (count % 2 != 0 && !isQueueEmpty(f2)) 
			appendQueue(res, popQueue(f2)); // f2 = [4 5 6] (pop) -> [5 6]
		
		count++;
	}

	return res;
}

Queue* inverteFila(Queue *q) { // O(n²)
	if (!q)
		return NULL;

	Queue* invertida = createQueue();

	int i = 0, j = 0;
	int pop;
	const int originalSize = q->size;
	int size = q->size - 1;
	while (i < originalSize) {
		while (j < size) {
			pop = popQueue(q);
			appendQueue(q, pop);
			j++;
		}
		pop = popQueue(q);
		appendQueue(invertida, pop);
		i++;
		j = 0;
		size--;
	}	

	return invertida;
}

void filhaEspelho(Queue* q) {
	if (!q)
		return;

	Queue *aux = createQueue();
	for (int i = 0; i < q->size; i++) 
		appendQueue(aux, q->vec[q->front + i]);

	Queue* inverte = inverteFila(aux); // [3 2 1]
	int j = 0;
	int size = inverte->size;
	while (j < size) {
		int pop = popQueue(inverte);
		appendQueue(q, pop);
		j++;
	}

	printQueue(q);
}
