#ifndef ALUNO_H
#define ALUNO_H

#define MAX 32

typedef struct {
    char nome[MAX];
    char tipo[MAX];
    int pc;
} Pokemon;

typedef struct {
    Pokemon *estoque;
    int tamanho;
    int capacidade;
} Estoque;

/*

------------------ Protótipos -------------------
      entrada e retorno a cargo do aluno

*/

Estoque* criaEstoque();
void liberarEstoque(Estoque **e);
void mostrarMaioresPorTipo(Estoque *e);
void mostrarRepetidos(Estoque *e);
void printPokemon(Pokemon p);

#endif