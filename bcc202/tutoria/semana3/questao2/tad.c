#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tad.h"

struct cidade {
    char nome[MAX];
    int numHabitantes;
    int escolas;
};

Cidade* alocarCidade(int n) {
    Cidade *c = (Cidade *) malloc(n * sizeof(Cidade));
    if (!c)
        return NULL;

    return c;
}

void destroiCidade(Cidade **c) {
    if (c)
        free((*c));

    (*c) = NULL;
}

int cidadeComMaisEscolas(Cidade* cidades, int num) {
    if (num == 1)
        return 0;

    int i = cidadeComMaisEscolas(cidades, num - 1);

    if (cidades[num - 1].escolas > cidades[i].escolas)
        return num - 1;
    else
        return i;
}

double calcularHabitantes(Cidade *cidades, int num) {
    if (num < 0)
        return 0;

    return cidades[num].numHabitantes + calcularHabitantes(cidades, num - 1);
}

void imprimeCidadePequena(Cidade *cidades, int num, int populacao) {
    if (num > 0) {
        if (cidades[num - 1].numHabitantes < populacao) 
            printf("Cidade %s - População: %d milhões\n", cidades[num - 1].nome, cidades[num - 1].numHabitantes);
        
        imprimeCidadePequena(cidades, num - 1, populacao);
    }
}

/*
Equação de recorrência de imprimeCidadePequena()

    Quando n = 0 -> retorna imediatamente, T(0) = c1;

    Quando n > 0:
        if (num > 0) => c2
        Comparação entre cidades[num - 1].numHabitantes e população => c3;
        Imprime o valor na tela => c3
        Chamada recursiva => T(n - 1) + c (onde c é a soma das 3 constantes acima)

    Expandindo achamos que o padrão é:
        T(n - k) + kc
        Como o caso base é T(0) -> n - k = 0 => n = k
        => T(0) + nc
        c1 + nc -> Equação de recorrência

Complexidade: O(n) pois as constantes podem ser desprezadas.
*/

void adicionaCidade(Cidade *cidade, char nome[MAX], int hab, int escola, int idx) {
    strcpy(cidade[idx].nome, nome);
    cidade[idx].numHabitantes = hab;
    cidade[idx].escolas = escola;
}

char *getNomeCidade(Cidade *cidades, int idx) {
    return cidades[idx].nome;
}