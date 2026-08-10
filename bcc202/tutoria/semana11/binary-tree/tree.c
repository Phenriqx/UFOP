#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

No* noCria(Registro reg);
void NoSucessor(No *pai, No **suc);

struct no {
    Registro reg;
    No* left;
    No* right;
};

No* noCria(Registro reg) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo) {
        novo->reg = reg;
        novo->left = NULL;
        novo->right = NULL;
    }

    return novo;
}

void ArvoreInicia(No **ppNo) {
    *ppNo = NULL;
}

bool ArvoreInsere(No **ppNo, Registro reg) {
    if (*ppNo == NULL) {
        *ppNo = noCria(reg);
        return (*ppNo) != NULL;
    }
    if (reg.chave < (*ppNo)->reg.chave)
        return ArvoreInsere(&(*ppNo)->left, reg);
    else if (reg.chave > (*ppNo)->reg.chave)
        return ArvoreInsere(&(*ppNo)->right, reg);

    return false;
}

bool ArvorePesquisa(No *pNo, Chave chave, Registro *pReg) {
    if (pNo == NULL)
        return false;

    if (chave < pNo->reg.chave)
        return ArvorePesquisa(pNo->left, chave, pReg);
    else if (chave > pNo->reg.chave)
        return ArvorePesquisa(pNo->right, chave, pReg);

    *pReg = pNo->reg;
    return true;
}

bool ArvoreRemove(No **ppNo, Chave chave, Registro *pReg) {
    // Não achar
    if (*ppNo == NULL)
        return false;

    // Menor
    if (chave < (*ppNo)->left->reg.chave)
        return ArvoreRemove(&(*ppNo)->left, chave, pReg);

    // Maior
    if (chave > (*ppNo)->right->reg.chave)
        return ArvoreRemove(&(*ppNo)->right, chave, pReg);

    // Igual
    *pReg = (*ppNo)->reg;

    // Nó folha
    if ((*ppNo)->left == NULL && (*ppNo)->right == NULL) {
        free(*ppNo);
        *ppNo = NULL;
    }

    // Só filho esq
    else if ((*ppNo)->left != NULL && (*ppNo)->right == NULL) {
        printf("No esq\n");
        No *aux = (*ppNo)->left;
        free(*ppNo);
        *ppNo = aux;
    }

    // Só filho dir
    else if ((*ppNo)->left == NULL && (*ppNo)->right != NULL) {
        No *aux = (*ppNo)->right;
        free(*ppNo);
        *ppNo = aux;
    }

    // Dois filhos
    else
        NoSucessor(*ppNo, &(*ppNo)->right);

    return true;
}

void NoSucessor(No *pai, No **suc) {
    if ((*suc)->left)
        return NoSucessor(pai, &(*suc)->left);
    pai->reg = (*suc)->reg;
    No *dir = (*suc)->right;
    free(*suc);
    *suc = dir;
}

void Central(No *pNo);
void PreFixa(No *pNo);
void PosFixa(No *pNo);

void Caminhamento(No *pNo, CAMINHAMENTO c) {
    if (c == PREORDER)
        PreFixa(pNo);
    else if (c == POSTORDER)
        PosFixa(pNo);
    else
        Central(pNo);
}

// inorder: left -> root -> right
void Central(No *pNo) {
    if (!pNo)
        return;

    Central(pNo->left);
    printRegistro(pNo->reg);
    printf("\n");
    Central(pNo->right);
}

// preorder: root -> left -> right
void PreFixa(No *pNo) {
    if (!pNo)
        return;

    printRegistro(pNo->reg);
    printf("\n");
    PreFixa(pNo->left);
    PreFixa(pNo->right);
}

// postorder: left -> right -> root
void PosFixa(No *pNo) {
    if (!pNo)
        return;

    PosFixa(pNo->left);
    PosFixa(pNo->right);
    printRegistro(pNo->reg);
    printf("\n");
}

void printRegistro(Registro reg){
    printf("[%2d | %s]", reg.chave, reg.nome);
}