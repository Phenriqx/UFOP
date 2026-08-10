#ifndef BINARIA_H
#define BINARIA_H

typedef struct registro Registro;
typedef struct dicionario Dicionario;

Dicionario* criarDicionario();
void freeDicionario(Dicionario **pDicio);
void dicioInsere(Dicionario *pDicio);
void printDicio(Dicionario *pDicio);

int binarySearch(Dicionario *dicio, int l, int r, int chave);

#endif