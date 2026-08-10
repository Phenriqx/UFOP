#ifndef ARVBINARIA_H
#define ARVBINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "auxiliares.h"

#define ITENS_PAG_ARV 12
#define NUM_MOLDURA_ARV 50

typedef struct {
    int pagina;   // -1 = sem filho
    int pos;     // posição dentro da página
} PonteiroNo;

typedef struct {
    Registro reg;
    PonteiroNo esq;
    PonteiroNo dir;
} No;

typedef struct {
    No nos[ITENS_PAG_ARV];
    int qntNos;
    int numPagina;   // -1 = vazia no buffer
    int frequencia;
} PaginaArv;

// buffer
PaginaArv* inicializaArv();
void destroiArv(PaginaArv *arv);
int buscarPaginaArv(PaginaArv *arv, int numPagina);
int escolherVitimaArv(PaginaArv *arv, bool *vazia);
int carregarPaginaArv(PaginaArv *arv, FILE *arq, int numPagina, Metricas *metricas);
void salvarPaginaArv(PaginaArv *arv, FILE *arq, int molduraIdx, Metricas *metricas);

// árvore
int criarArvBinaria(Config *config, FILE *arqOriginal, const char *arqArvBin, Metricas *metricas);
void insereNo(FILE *arq, PaginaArv *arv, Registro reg, int *totalPaginas, Metricas *metricas);
bool pesquisaArvoreBinaria(FILE *arq, PaginaArv *arv, Registro *reg, Metricas *metricas);
No inicializaNo(Registro reg);

#endif