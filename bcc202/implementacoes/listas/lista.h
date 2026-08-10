#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

typedef struct node Node;
typedef struct celula Celula;
typedef struct lista Lista;

Lista* createLinkedList();
void freeLinkedList(Lista **lista);
void insertAtEnd(Lista *lista, int val);
void removeAtEnd(Lista *lista);
void insertAtBeginning(Lista *lista, int val);
void removeAtBeginning(Lista *lista);

int recursiveSum(Lista *lista);
void moveElementList(Lista *lista, int val);
void listaTemNumerosRepetidos(Lista *lista);
void listaInverteParte(Lista *lista, int pos);
void moveMenor(Lista *lista);

int sizeLinkedList(Lista *lista);
bool isListEmpty(Lista *lista);
void printLinkedList(Lista *lista);

#endif
