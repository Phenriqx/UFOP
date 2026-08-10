#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void toLowerAll(Chave c);

// Manter como especificado
void inicia(Hash *hash, int m, int p) {
    hash->m = m;
    hash->p = p;
    hash->chaves = (Chave *) malloc(sizeof(Chave) * m);
    if (!hash->chaves)
        return;

    hash->pesos = (int *) malloc(sizeof(int) * p);
    if (!hash->pesos)
        return;

    for (int i = 0; i < m; i++)
        hash->chaves[i][0] = '\0';
}

// Manter como especificado
void libera(Hash *hash) {
    if (hash != NULL) {
        if (hash->chaves != NULL)
            free(hash->chaves);

        if (hash->pesos != NULL)
            free(hash->pesos);
    }
}

int H(Hash* hash, Chave chave) {
    int soma = 0;
    int j = 0;

    for (int i = 0; chave[i] != '\0'; i++) {
        if (isalpha(chave[i])) {
            char c = tolower(chave[i]);

            soma += (int) c * hash->pesos[j % hash->p];
            j++;
        }
    }

    return soma % hash->m;
}

// Manter como especificado
int insere (Hash *hash, Chave chave) {
    int pos_inicial = H(hash, chave);
    int pos_atual;

    for (int i = 0; i < hash->m; i++) {
        pos_atual = (pos_inicial + i) % hash->m;

        if (hash->chaves[pos_atual][0] == '\0') {
            strcpy(hash->chaves[pos_atual], chave);
            return pos_atual;
        }

        toLowerAll(hash->chaves[pos_atual]);
        toLowerAll(chave);
        if (strcmp(hash->chaves[pos_atual], chave) == 0)
            return -1;

    }

    return -1;
}

void toLowerAll(Chave c) {
    for (int i = 0; c[i] != '\0'; i++)
        c[i] = tolower(c[i]);
}