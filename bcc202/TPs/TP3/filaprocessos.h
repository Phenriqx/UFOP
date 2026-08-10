#ifndef FILAPROCESSOS_H
#define FILAPROCESSOS_H

#include <stdbool.h>

#define TAM 32

typedef struct pilhaExecucao PilhaExecucao;
typedef struct escopo Escopo;
typedef struct no No;
typedef struct registro Registro;

PilhaExecucao* criarPilha();
int destroiPilha(PilhaExecucao **ppPilha);
void adicionaPilha(PilhaExecucao *pPilha);
int executar(const char *nomeArquivo, PilhaExecucao* pPilha);
void removePilha(PilhaExecucao *pPilha);
void leValor(FILE *file, PilhaExecucao *pPilha);
void adicionarNaArvore(PilhaExecucao *pPilha, No *novo);
void adicionaRecursivo(No *raiz, No *novo);
int procuraArvore(No *raiz, const char nome[TAM]);
int imprimir(FILE *file, PilhaExecucao *pPilha);
int lePalavras(FILE* file);

Escopo* criarEscopo();
void destroiEscopo(Escopo **ppEscopo);

#endif