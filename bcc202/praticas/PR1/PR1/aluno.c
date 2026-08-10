#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

Estoque* criaEstoque() {
    Estoque *e = (Estoque *) malloc(sizeof(Estoque));
    if (!e) {
        printf("Erro ao alocar memoria\n");
        return NULL;
    }

    e->capacidade = 2;
    e->tamanho = 0;

    e->estoque = (Pokemon *) malloc(sizeof(Pokemon) * e->capacidade);
    if (!e->estoque) {
        printf("Erro ao alocar memoria\n");
        return NULL;
    }
 
    return e;
}

void liberarEstoque(Estoque **e) {
    free((*e)->estoque);
    (*e)->estoque = NULL;
    free(*e);
    *e = NULL;
}

void mostrarMaioresPorTipo(Estoque *e) {
    Pokemon pokemons[e->tamanho];
    int max = 0;

    for (int i = 0; i < e->tamanho; i++) {
        char *tipo_atual = e->estoque[i].tipo; // na primeira iteração é o tipo do primeiro pokemon da lista
        int pc_atual = e->estoque[i].pc; // na primeira iteração é o pc do primeiro pokemon da lista

        int found = 0;
        for (int j = 0; j < max; j++) {
            if (!strcmp(pokemons[j].tipo, tipo_atual)) {
                found = 1;

                if (pc_atual > pokemons[j].pc) {
                    pokemons[j].pc = pc_atual;
                    strcpy(pokemons[j].nome, e->estoque[i].nome);
                }
                break;
            }
        }

        if (!found) {
            strcpy(pokemons[max].tipo, tipo_atual);
            pokemons[max].pc = pc_atual;
            strcpy(pokemons[max].nome, e->estoque[i].nome);
            max++;
        }
    }

    for (int i = 0; i < max; i++) {
        printPokemon(pokemons[i]);
    }
}

void mostrarRepetidos(Estoque *e){
    int repetido[e->tamanho]; // marca quais índices do vetor são repetidos
    for (int i = 0; i < e->tamanho; i++)
        repetido[i] = 0;

    for (int i = 0; i < e->tamanho; i++) {
        if (repetido[i])
            continue;

        int count = 0;

        for (int j = i + 1; j < e->tamanho; j++) { // j é sempre 1 unidade a frente de i, contando os valores a frente no vetor.
            if (!strcmp(e->estoque[i].nome, e->estoque[j].nome)) {
                repetido[j] = 1;
                count++;
            }
        }

        if (count > 0)
            printf("%s\n", e->estoque[i].nome);        
    }
}

void printPokemon(Pokemon p) {
    printf("%s: %s\n", p.tipo, p.nome);
}