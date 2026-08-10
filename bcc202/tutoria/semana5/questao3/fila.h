#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;
typedef struct item Item;

Fila* criarFila();
void freeFila(Fila** f);
void insertFila(Fila *f, Item* i);
int popFila(Fila *f);
void printFila(Fila *f);
Item* criaItem(int val);

#endif
