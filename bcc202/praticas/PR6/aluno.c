#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

void insereDicionario(Dicionario *d, char *palavra, char *definicao) {
    if (d->tam < 100) {
        strcpy(d->itens[d->tam].palavra, palavra);
        strcpy(d->itens[d->tam].definicao, definicao);
        d->tam++;
    }
    else
        printf("Dicionário cheio!\n");
}

COMPARA comparaElemento(char* c1, char* c2) {
    if (strcmp(c1, c2) < 0)
        return MENOR;
    else if (strcmp(c1, c2) > 0)
        return MAIOR;
    else
        return IGUAL;
}

void ShellSort(Elemento *r, int n) {
    int h=1, i, j;
    Elemento aux;
    for (h = 1; h < n; h = 3 * h + 1);

    while (h > 1) {
        h = (h - 1) / 3;
        for (i=h;i<n;i++) {
            aux = r[i];
            j = i - h;
            while (j >= 0 && comparaElemento(r[j].palavra, aux.palavra) == MAIOR) {
                r[j + h] = r[j];
                j -= h;
            }
            r[j + h] = aux;
        }
    }
}

int buscaBinaria(Dicionario d, char *chave) {
    int l = 0;
    int r = d.tam - 1;
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        if (comparaElemento(chave, d.itens[m].palavra) == MENOR)
            r = m - 1;
        else {
            if (comparaElemento(chave, d.itens[m].palavra) == MAIOR)
                l = m + 1;
            else
                return m;
        }
    }
    return -1;
}