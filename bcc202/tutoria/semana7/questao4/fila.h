#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;

Fila* criaFila();
void destroiFila(Fila **f);
void filaEnfileira(Fila *f, int val);
int filaDesenfileira(Fila *f);
void printFila(Fila* f);

#endif
