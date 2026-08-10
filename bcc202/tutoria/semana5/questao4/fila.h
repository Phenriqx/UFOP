#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;
typedef struct aluno Aluno;

Fila* criarFila();
void freeFila(Fila** f);
void insertFila(Fila *f, Aluno *a);
int popFila(Fila *f);
void printFila(Fila *f);
Aluno* criaAluno(int matricula, char nome[]);

#endif
