#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

// Definição das structs
struct pessoa {
    char nome[50];
    int idade;
};

struct celula {
    Pessoa dado;		
    struct celula *prox;
};

struct lista {
    Celula *primeiro;
};

Lista* criaLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (!lista)
	return NULL;

    lista->primeiro = NULL;
    return lista;
}

void listaPush(Lista* l, char *nome, int idade) { // O(1) no melhor caso; O(n) no caso médio e pior caso
    if (!l)
	return;

    Celula *novo = (Celula*) malloc(sizeof(Celula));
    strcpy(novo->dado.nome, nome);
    novo->dado.idade = idade;
    novo->prox = NULL;

    if (!l->primeiro || idade < l->primeiro->dado.idade) {
        novo->prox = l->primeiro;
        l->primeiro = novo;
    } 
    else {
        Celula *atual = l->primeiro;

        while (atual->prox != NULL && atual->prox->dado.idade < idade) {
            atual = atual->prox;
        }

        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

void printLista(Lista* l) {
    if (!l || l->primeiro == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Celula *aux = l->primeiro;
    while (aux != NULL) {
        printf("Nome: %-10s | Idade: %d\n", aux->dado.nome, aux->dado.idade);
        aux = aux->prox;
    }
    printf("\n");
}
