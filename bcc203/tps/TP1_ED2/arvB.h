#ifndef ARVB_H
#define ARVB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "auxiliares.h"

#define M 4

typedef long TipoApontador; // aqui o TipoApontador vira um long para representar a posição no arquivo

typedef struct TipoPagina {
    short n;
    Registro r[2 * M];
    TipoApontador p[(2 * M) + 1];
} TipoPagina;

#define NUM_MOLDURA_B 50


typedef struct {
    TipoPagina pagina;
    TipoApontador enderecoDisco; // -1 significa que a moldura está vazia
    int frequencia;
} MolduraB;

MolduraB* inicializaMolduraB();
void destroiMolduraB(MolduraB *buffer);
int buscarMolduraB(MolduraB *buffer, TipoApontador endereco);
int escolherVitimaB(MolduraB *buffer, bool *vazia);
int carregarPaginaB(MolduraB *buffer, FILE *arq, TipoApontador endereco, Metricas *metricas);
void pesquisaArvoreBBuffer(Registro *reg, Metricas *metricas, bool *encontrado, TipoApontador pos, FILE *arq,MolduraB *buffer);


int criarArvB(Config* config, FILE* arqOriginal, const char *arqArvB, Metricas *metricas);
void pesquisaArvoreB(Registro *reg, Metricas *metricas, bool *encontrado, TipoApontador pos, FILE *arq);
void insereNaPagina(TipoPagina *Ap, Registro reg, TipoApontador ApDir,Metricas *metricas);
void insNoDisco(FILE* arq, Registro reg, TipoApontador posAtual, short *cresceu, Registro *regRetorno, TipoApontador* posRetorno,Metricas *metricas);
void insere(Registro reg, FILE* arqB, TipoApontador *posAtual,Metricas *metricas);

TipoPagina* criaPagina();
void lerNo(FILE* arqB, TipoApontador pos, TipoPagina* ap,Metricas *metricas);
void escreverNo(FILE* arqB, TipoApontador pos, TipoPagina *ap,Metricas *metricas);
TipoApontador criarNo(FILE *arq, TipoPagina *no,Metricas *metricas);
void acharPosicaoRaiz(FILE *arq, TipoApontador* posReal);

#endif