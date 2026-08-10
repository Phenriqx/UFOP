#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lista.h"

struct celula {
	Celula *next;
	int node;
};

struct lista {
	Celula *head;
	Celula *tail;
	int n;
};

Lista* createLinkedList() {
	Lista *lista = (Lista *)malloc(sizeof(Lista));
	if (!lista)
		return NULL;

	lista->head = (Celula *) malloc(sizeof(Celula));
	if (!lista->head)
		return NULL;

	lista->head->next = NULL;
	lista->tail = lista->head;
	lista->n = 0;
	
	return lista;
}

void insertAtEnd(Lista* lista, int val) {
	if (!lista)
		return;
	
	lista->tail->next = (Celula *)malloc(sizeof(Celula));
	lista->tail = lista->tail->next;
	lista->tail->node = val;
	lista->tail->next = NULL;
	lista->n++;
}

void removeAtEnd(Lista* lista) {
	if (!lista || isListEmpty(lista))
		return;
	
	int i = 0;	
	Celula *aux = (Celula*) malloc(sizeof(Celula));
		aux = lista->head;
	while (i < lista->n - 1 && aux->next) {
		aux = aux->next;	
		i++;
	}

	lista->tail = aux;
	lista->tail->next = NULL;
	lista->n--;
}

void insertAtBeginning(Lista* lista, int val) {
	if (!lista)
		return;

	Celula *newCell = (Celula *)malloc(sizeof(Celula));
	if (!newCell)
		return;
	
	newCell->next = lista->head->next;
	lista->head->next = newCell;
	newCell->node = val;
	lista->n++;
}

void removeAtBeginning(Lista *lista) {
	if (!lista || isListEmpty(lista))
		return;

	if (lista->n == 0) {
		lista->head->next = NULL;
		return;
	}

	lista->head->next = lista->head->next->next;
	lista->n--;
}

void printLinkedList(Lista* lista) {
	printf("[ ");
	Celula *temp = (Celula* ) malloc(sizeof(Celula));
	temp = lista->head;

	while (temp->next) {
		printf("%d ", temp->next->node);
		temp = temp->next;
	}
	printf("]\n");
}

int sizeLinkedList(Lista *lista) {
	if (lista)
		return lista->n;

	return -1;
}

bool isListEmpty(Lista *lista) {
	if (lista)
		if (lista->n == 0)
			return true;

	return false;

}

int sumNodes(Celula *cell);

int recursiveSum(Lista* lista) {
	if (!lista || isListEmpty(lista))
		return -1;

	return sumNodes(lista->head->next);
}

int sumNodes(Celula *cell) {
	if (!cell)
		return 0;

	return cell->node + sumNodes(cell->next);
}

void moveElementList(Lista *lista, int val) {
	if (!lista || isListEmpty(lista))
		return;

	Celula *aux = lista->head;
	while (aux->next->node != val && aux->next)
		aux = aux->next;

	Celula *temp1 = aux;
	Celula *temp2 = aux->next;
	Celula *temp3 = temp2->next;

	temp2->next = lista->head->next;
	lista->head->next = temp2;
	temp1->next = temp3;
}

void listaInverteParte(Lista *lista, int pos) {
	if (!lista || isListEmpty(lista))
		return;

	Celula* prev_start = lista->head;
	Celula* start = prev_start->next;
	Celula* next_block = start;
	int i = 0;
	while (i < pos + 1 && next_block) {
		next_block = next_block->next;
		i++;
	}

	Celula* curr = start;
	Celula* prev = NULL;
	Celula* next_node = NULL;

	while (curr != next_block) {
		next_node = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next_node;
	}

	lista->head->next = prev;
	start->next = next_block;
}

void moveMenor(Lista *lista) {
	if (!lista)
		return;

	Celula *aux = lista->head;
	Celula *minPrev = aux->next;
	while (aux->next) {
		if (aux->next->node < minPrev->next->node)
			minPrev = aux;
		aux = aux->next;
	}

	Celula *temp1 = minPrev;
	Celula *min = minPrev->next;
	Celula *temp2 = min->next;

	min->next = lista->head->next;
	lista->head->next = min;
	temp1->next = temp2;
}
