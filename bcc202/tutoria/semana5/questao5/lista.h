#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;
typedef struct celula Celula;
typedef struct pessoa Pessoa;

Lista* criaLista();
void listaPush(Lista* l, char *nome, int idade);
void printLista(Lista *l);

#endif
