#include <stdlib.h>
#include <stdio.h>

#include "pilha_pont.h"

struct celula {
	int val;
	struct celula *prox;
};

struct pilha {
	Celula *topo;
	size_t size;
};

Pilha* criaPilhaPont() { 
	Pilha *p = (Pilha *) malloc(sizeof(Pilha));
	if (p) {
		p->size = 0;
		p->topo = (Celula *) malloc(sizeof(Celula));
		if (!p->topo) {
			free(p);
			return NULL;
		}

		p->topo->prox = NULL;
	}	

	return p;
}

int pilhaEhVaziaPont(Pilha *p) { // O(1)
	return p->size == 0;
}

void pilhaPushPont(Pilha *p, int val) { // O(1)
	if (!p)
		return;

	Celula* newCell = (Celula *) malloc(sizeof(Celula));
	if (!newCell)
		return;

	newCell->val = val;
	newCell->prox = p->topo->prox;
	p->topo->prox = newCell;
	p->size++;
}

int pilhaPopPont(Pilha *p) { // O(1)
	if (!p || pilhaEhVaziaPont(p))
		return -1;
	
	int pop = p->topo->prox->val;
	p->topo = p->topo->prox;
	p->size--;
	return pop;
}


void printPilhaPont(Pilha *p) { // O(n) 
    if (!p)
        return;

    printf("[");
    Celula *aux = p->topo->prox;
    while (aux) {
		printf(" %d ", aux->val);
        aux = aux->prox;
    }    
    printf("]\n");
}
