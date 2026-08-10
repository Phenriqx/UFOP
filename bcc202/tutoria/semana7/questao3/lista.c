#include <stdlib.h>
#include <stdio.h>

#include "lista.h"

struct celula {
	int item;
	struct celula *prox;
};

struct lista {
	Celula* cabeca;
	Celula *ultimo;
	int tam;
};

Lista* criaLista() {
	Lista *l = (Lista* ) malloc(sizeof(Lista));
	if (l) {
		l->cabeca = (Celula *) malloc(sizeof(Celula));
		if (!l->cabeca) {
			free(l);
			return NULL;
		}
	}

	l->cabeca->prox = NULL;
	l->ultimo = l->cabeca;
	l->tam = 0;
	
	return l;
}

void freeLista(Lista **lista) {
    if (!lista || !(*lista)) {
        return; 
    }

    Lista *pLista = *lista; 

    Celula *atual = pLista->cabeca; 
    Celula *proximo;

    while (atual != NULL) {
        proximo = atual->prox; 
        free(atual);           
        atual = proximo;    
    }

    free(pLista); 

    *lista = NULL;
}

void inserirFim(Lista *lista, int val) {
	if (!lista)
		return;

	lista->ultimo->prox = (Celula *) malloc(sizeof(Celula));
	lista->ultimo = lista->ultimo->prox;
	lista->ultimo->item = val;
	lista->ultimo->prox = NULL;
	lista->tam++;
}

void printLista(Lista *lista) {
	if (!lista)
		return;

	printf("[ ");
	Celula *temp = (Celula* ) malloc(sizeof(Celula));
	temp = lista->cabeca;

	while (temp->prox) {
		printf("%d ", temp->prox->item);
		temp = temp->prox;
	}
	printf("]\n");
}

void removeMaior(Lista *lista) {
	if (!lista)
		return;
	
	Celula *temp = lista->cabeca;
	Celula *aux;
	int i = 0;
	while (i < 3 && temp->prox) {
		if (temp->prox->item > 10) {
			aux = temp->prox;	
			temp->prox = aux->prox;
			i++;
			free(aux);
		}
		else 
			temp = temp->prox;
	}

	printLista(lista);
	inverterLista(lista);
}

void inverterLista(Lista *lista) {
	if (!lista)
		return;
	
	Celula *prev = NULL;
	Celula *curr = lista->cabeca->prox;
	Celula *next = NULL;

	lista->ultimo = lista->cabeca->prox;

	while (curr) {
		next = curr->prox;
		curr->prox = prev;
		prev = curr;
		curr = next;
	}

	lista->cabeca->prox = prev;
}
