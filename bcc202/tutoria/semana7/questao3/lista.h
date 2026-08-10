#ifndef LISTA_H
#define LISTA_H

typedef struct celula Celula;
typedef struct lista Lista;

Lista* criaLista();
void freeLista(Lista **lista);
void inserirFim(Lista* lista, int val);
void printLista(Lista* lista);
void removeMaior(Lista* lista);
void inverterLista(Lista* lista);

#endif
