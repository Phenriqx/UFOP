#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct node {
	int val;
	struct node *next;
};

struct list {
	Node* head;
	Node* tail;
	size_t n;
};

List* createList() {
	List *list = (List *) malloc(sizeof(List));
	if (list) {
		list->n = 0;
		list->head = (Node*) malloc(sizeof(Node));
		if (!list->head) {
			free(list);
			return NULL;
		}

		list->head->next = NULL;
		list->tail = list->head;
	}

	return list;
}

void insertList(List* list, int val) {
	if (!list)
		return;
	
	list->tail->next = (Node*) malloc(sizeof(Node));
	list->tail = list->tail->next;
	list->tail->val = val;
	list->tail->next = NULL;
	list->n++;
}

void tradePositions(List *list, int idx) {
	if (!list)
		return;

	int j = 0;
	Node* aux = list->head;
	while (j < idx && aux->next->next) {
		aux = aux->next;
		j++;
		if (!aux->next->next) {
			printf("Não eh possível trocar item na última posição\n");
			return;
		}
	}

	Node *temp1 = aux->next;
	Node *temp2 = temp1->next;
	Node *temp3 = temp2->next;

	aux->next = temp2;
	temp2->next = temp1;
	temp1->next = temp3;
}

void printList(List* list) {
	if (!list)
		return;

	Node *aux = list->head;
	while(aux->next) {
		aux = aux->next;
		printf("%d ", aux->val);
	}
	printf("\n");
}
