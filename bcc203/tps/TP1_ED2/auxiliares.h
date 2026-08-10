#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define Chave_Teste 0

typedef struct {
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[5000];
} Registro;

typedef struct {
    int transferencias;
    int comparacoes;
    double tempo;
} Metricas;

typedef struct{
    int metodo;
    int qnt_registros;
    int situacao;
    int chave;
    bool p;
} Config;

bool validaEntrada(int argc, char *argv[],Config *config);
int criarArquivo(const char* caminho, int qnt_registros, int situacao);
void preencherDados(Registro *reg);
void printRegistro(Registro reg, Metricas metricas, bool encontrado, const char* nomeArquivo,Config config);
void printCriaReg(Metricas metricas);

int* criaVetor(int tamanho);
void destroiVetor(int *vet);
void inicializaMetricas(Metricas *metricas);
void criarArquivoAleatorio(FILE* arquivo, int qnt_registros);

#include "arvBinaria.h"
#include "acessoSequencial.h"
#include "arvB.h"
#include "arvBE.h"

void modoAut1(FILE *arquivo, int *vetorIndices, int numPaginas, Moldura *moldura, Config *config);
void modoAut2(FILE *arqArv, PaginaArv *buffer, Config *config);
void modoAut3(FILE *arq, Config *config, TipoApontador posRaizReal,MolduraB *buffer);
void modoAut4(TipoApontadorBE* Ap,  Config *config);

#endif