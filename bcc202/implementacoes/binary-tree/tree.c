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

void imprimeNos(No *pNo, int a, int b) {
    if (!pNo)
        return;

    if (pNo->reg.chave <= a)
        printf("%d ", pNo->reg.chave);
    else if (pNo->reg.chave >= b)
        printf("%d ", pNo->reg.chave);

    imprimeNos(pNo->left, a, b);
    imprimeNos(pNo->right, a, b);
}

void helper(No *pNo, float *soma, int *count);

float mediaNosPar(No *pNo) {
    float soma = 0;
    int count = 0;

    helper(pNo, &soma, &count);
    float media;
    if (count > 0)
        media = soma / count;

    return media;
}

void helper(No *pNo, float *soma, int *count) {
    if (!pNo)
        return;

    if (pNo->reg.chave % 2 == 0) {
        *soma += pNo->reg.chave;
        *count += 1;
    }
    helper(pNo->left, soma, count);
    helper(pNo->right, soma, count);
}

void imprimeDecrescente(No *pNo) {
    if (!pNo)
        return;

    imprimeDecrescente(pNo->right);
    printf("%d ", pNo->reg.chave);
    imprimeDecrescente(pNo->left);
}

int produtoArvore(No *pNo) {
    if (!pNo)
        return 1;

    return pNo->reg.chave * produtoArvore(pNo->left) * produtoArvore(pNo->right);
}

int menorNoFolha(No *pNo, int nivel) {
    if (!pNo)
        return 0;
    if (!pNo->left && !pNo->right)
        return 1;

    
}

void printRegistro(Registro reg){
    printf("[%2d | %s]", reg.chave, reg.nome);
}