#ifndef ALUNO_H
#define ALUNO_H

#include <stdbool.h>

#define MAX 32

typedef struct {
    char palavra[MAX];
    int frequencia;
} Registro;

typedef struct no No;

typedef enum {
    MENOR = 0,
    IGUAL,
    MAIOR
} COMPARA;

void arvoreInicia(No **ppNo);
No* noCria(Registro reg);
void arvoreLibera(No **ppNo);
bool arvoreInsere(No **ppNo, Registro reg);
bool arvorePesquisa(No *pNo, Registro reg, Registro *pReg);

void printInOrder(No *pNo);
void printRegistro(Registro reg);

COMPARA comparaRegistro(Registro r1, Registro r2);

#endif