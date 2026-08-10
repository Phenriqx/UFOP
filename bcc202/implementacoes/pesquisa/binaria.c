#include <stdio.h>
#include <stdlib.h>

#include "binaria.h"

struct registro {
    int chave;
};

struct dicionario {
    Registro *vec;
    int n, max;
};

Dicionario* criarDicionario() {
    Dicionario* dicio = (Dicionario *) malloc(sizeof(Dicionario));
    if (dicio) {
        dicio->n = 0;
        dicio->max = 10;
        dicio->vec = (Registro *) malloc(sizeof(Registro) * dicio->max);
        if (!dicio->vec) {
            free(dicio);
            return NULL;
        }
    }

    return dicio;
}

void freeDicionario(Dicionario **pDicio) {
    if (!*pDicio || !pDicio)
        return;

    free((*pDicio)->vec);
    free(*pDicio);
    *pDicio = NULL;
}

void dicioInsere(Dicionario *pDicio) {
    if (!pDicio)
        return;

    for (int i = 0; i < pDicio->max; i++)
        pDicio->vec[i].chave = i + 1;
}

void printDicio(Dicionario *pDicio) {
    for (int i = 0; i < pDicio->n; i++)
        printf("%d ", pDicio->vec[i].chave);
}

int binarySearch(Dicionario *dicio, int l, int r, int chave) {
    int m = (l + r) / 2;

    if (dicio->vec[m]. chave != chave && l == r)
        return -1;
    if (chave < dicio->vec[m].chave)
        return binarySearch(dicio, l, m - 1, chave);
    else if (chave > dicio->vec[m].chave)
        return binarySearch(dicio, m + 1, r, chave);
    else
        return m;
}