#ifndef TAD_H
#define TAD_H

typedef struct cidade Cidade;

#define MAX 64

Cidade *alocarCidade(int n);
void destroiCidade(Cidade **c);
void adicionaCidade(Cidade *cidade, char nome[MAX], int hab, int escola, int idx);

int cidadeComMaisEscolas(Cidade *cidades, int num);
double calcularHabitantes(Cidade *cidades, int num);
void imprimeCidadePequena(Cidade *cidades, int num, int populacao);

// getters

char *getNomeCidade(Cidade *cidades, int idx);

#endif