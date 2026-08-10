#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef int Chave;

typedef struct {
    int chave;
    char nome[21];
} Registro;

typedef enum {
    PREORDER = 0,
    INORDER,
    POSTORDER
} CAMINHAMENTO;

typedef struct no No;
typedef No* Arvore;

void ArvoreInicia(No **ppNo);
bool ArvoreInsere(No **ppno, Registro reg);
bool ArvorePesquisa(No *pNo, Chave chave, Registro *pReg);
bool ArvoreRemove(No **ppNo, Chave chave, Registro *pReg);

void Caminhamento(No *pNo, CAMINHAMENTO c);

void imprimeNos(No *pNo, int a, int b);
float mediaNosPar(No *pNo);
void imprimeDecrescente(No *pNo);
int produtoArvore(No *pNo);
int menorNoFolha(No *pNo, int nivel);

void printRegistro(Registro reg);

#endif