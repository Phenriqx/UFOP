#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

struct no {
    Registro reg;
    No* left;
    No* right;
};

void arvoreInicia(No **ppNo) {
    *ppNo = NULL;
}

No* noCria(Registro reg) {
    No* pNo = (No* ) malloc(sizeof(No));
    if (pNo) {
        pNo->reg = reg;
        pNo->left = NULL;
        pNo->right = NULL;
    }

    return pNo;
}

bool arvoreInsere(No **ppNo, Registro reg) {
    if (!*ppNo) {
        *ppNo = noCria(reg);
        return *ppNo != NULL;
    }

    // se o registro já estiver na árvore, incrementa sua frequência
    Registro pReg;
    if (arvorePesquisa(*ppNo, reg, &pReg)) {
        No *aux = *ppNo;
        while (aux) {
            if (comparaRegistro(reg, aux->reg) == IGUAL) {
                aux->reg.frequencia++;
                return true;
            }
            else if (comparaRegistro(reg, aux->reg) == MENOR)
                aux = aux->left;
            else
                aux = aux->right;
        }
    }

    // caso contrário o adiciona na árvore na devida posição
    if (comparaRegistro(reg, (*ppNo)->reg) == MENOR)
        return arvoreInsere(&(*ppNo)->left, reg);
    else if (comparaRegistro(reg, (*ppNo)->reg) == MAIOR)
        return arvoreInsere(&(*ppNo)->right, reg);

    return false;
}

bool arvorePesquisa(No *pNo, Registro reg, Registro *pReg) {
    if (!pNo)
        return false;

    if (comparaRegistro(reg, pNo->reg) == MENOR)
        return arvorePesquisa(pNo->left, reg, pReg);
    else if (comparaRegistro(reg, pNo->reg) == MAIOR)
        return arvorePesquisa(pNo->right, reg, pReg);

    *pReg = pNo->reg;
    return true;
}

void printInOrder(No *pNo) {
    if (pNo) {
        printInOrder(pNo->left);
        printRegistro(pNo->reg);
        printInOrder(pNo->right);
    }
}

void printRegistro(Registro reg) {
    printf("%s: %d\n", reg.palavra, reg.frequencia);
}

void arvoreLibera(No **ppNo) {
    if (!*ppNo)
        return;

    arvoreLibera(&(*ppNo)->left);
    arvoreLibera(&(*ppNo)->right);

    free(*ppNo);
    *ppNo = NULL;
}

COMPARA comparaRegistro(Registro r1, Registro r2) {
    if (strcmp(r1.palavra, r2.palavra) < 0)
        return MENOR;
    else if (strcmp(r1.palavra, r2.palavra) > 0)
        return MAIOR;
    else
        return IGUAL;
}