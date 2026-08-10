#ifndef ALUNO_H
#define ALUNO_H

typedef struct {
    char palavra[100];
    char definicao[100];
} Elemento;

typedef struct {
    Elemento itens[100];
    int tam;
} Dicionario;

typedef enum {
    MENOR=0,
    IGUAL,
    MAIOR
} COMPARA;

void insereDicionario(Dicionario *d, char *palavra, char *definicao);
COMPARA comparaElemento(char* c1, char* c2);
void ShellSort(Elemento *r, int n);

int buscaBinaria(Dicionario d, char *chave);

#endif
