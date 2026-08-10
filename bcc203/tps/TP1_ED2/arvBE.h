#ifndef ARVBE_H
#define ARVBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auxiliares.h"

#define M 4

typedef long Chave;
typedef enum {Interna, Externa} TipoIntExt;
typedef struct TipoPaginaBE* TipoApontadorBE;

typedef struct TipoPaginaBE {
    TipoIntExt tipoPag;
    union {
        struct {
            int ni;
            Chave ri[2 * M];
            TipoApontadorBE pi[(2 * M) + 1];
        } pagInterna;
        struct {
            int ne;
            Registro re[2 * M];
        } pagExterna;
    } pag;
} TipoPaginaBE;

void pesquisaArvoreBE(Registro *reg, TipoApontadorBE *Ap, bool *encontrado, Metricas *metricas);
void criarArvoreBE(Config* config, Metricas *metricas, TipoApontadorBE *arvoreBE, FILE* arqOriginal);
void insereArvoreBE(TipoApontadorBE *Ap, Registro reg);
void liberaArvoreBE(TipoApontadorBE Ap);

void inserePaginaInterna(TipoApontadorBE Ap, TipoApontadorBE ApDir, Chave retorno);
void inserePaginaExterna(TipoApontadorBE Ap, Registro reg);
void splitInterno(TipoApontadorBE Ap, TipoApontadorBE *ApRetorno, Registro *regRetorno, Chave retorno, TipoApontadorBE apFilhoDir);

#endif