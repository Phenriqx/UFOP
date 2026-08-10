#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filaprocessos.h"

struct registro {
    char nome[TAM];
    char valor[TAM];
};

struct no {
    Registro reg;
    struct no *left;
    struct no *right;
};

struct escopo {
    No* raiz;
    struct escopo *next;
    int n;
};

struct pilhaExecucao {
    Escopo *topo;
    int n;
};

No* noCria(Registro reg);
void destroiArvore(No **ppNo);

PilhaExecucao* criarPilha() {
    PilhaExecucao* pilha =(PilhaExecucao* ) malloc(sizeof(PilhaExecucao));
    if (pilha) {
        pilha->n = 0;
        pilha->topo = NULL;
    }

    return pilha;
}

//Destroi toda a pilha
//Se retornar 1 significa que tinha pilhas que n]ao tiveram end
int destroiPilha(PilhaExecucao **ppPilha) {
    int value = 1;
    if (!ppPilha || !*ppPilha)
        return 0;
    Escopo *e = (*ppPilha)->topo;
    if(e == NULL)
        value = 3;

    while (e) {
        Escopo *prox = e->next;
        destroiArvore(&e->raiz);
        free(e);
        e = prox;
    }
    (*ppPilha)->topo = NULL;
    free(*ppPilha);
    *ppPilha = NULL;

    return value;
}

Escopo* criarEscopo() {
    Escopo* escopo = (Escopo* ) malloc(sizeof(Escopo));
    if (escopo) {
        escopo->n = 0;
        escopo->next = NULL;
        escopo->raiz = NULL;
    }

    return escopo;
}

No* noCria(Registro reg) {
    No* pNo = (No *) malloc(sizeof(No));
    if (pNo) {
        pNo->reg = reg;
        pNo->left = NULL;
        pNo->right = NULL;
    }

    return pNo;
}

//Cria um escopo e adiciona na pilha
void adicionaPilha(PilhaExecucao *pPilha) {
    if (!pPilha)
        return;

    Escopo* e = criarEscopo();
    if(!e) return;
    //realmente atua como uma pilha, LIFO
    e->next = pPilha->topo;
    pPilha->topo = e;
    pPilha->n++;
}


void adicionarNaArvore(PilhaExecucao *pPilha, No *novo){
    if (!pPilha || !pPilha->topo || !novo) return;
    // se não houver uma árvore ainda inicia ela, adicionando o Nó novo como a raiz
    if (pPilha->topo->raiz == NULL){

        pPilha->topo->raiz = novo;
        return;
    }

    adicionaRecursivo(pPilha->topo->raiz, novo);
}

//adiciona na ABB o No *novo
void adicionaRecursivo(No *raiz, No *novo){

    if (!raiz || !novo) return;

    int cmp = strcmp(novo->reg.nome, raiz->reg.nome);

    if (cmp == 0) {
        // mesma variável: atualiza valor e descarta o nó novo
        strcpy(raiz->reg.valor, novo->reg.valor);
        free(novo);
        return;
    }

    if (cmp < 0){
        if(raiz->left == NULL){
            raiz->left = novo;
            return;
        }
        adicionaRecursivo(raiz->left, novo);
    }
    if (cmp > 0){
        if(raiz->right == NULL){
            raiz->right = novo;
            return;
        }
        adicionaRecursivo(raiz->right, novo);
    }
}

//função que procura e imprimi se tiver na árvore, o nome nesse caso é a chave do registro
int procuraArvore(No *raiz, const char nome[TAM]){
    if (!raiz)
        return 0;

    int cmp = strcmp(raiz->reg.nome, nome);

    if (cmp == 0) {
        printf("%s\n", raiz->reg.valor);
        return 1;
    }

    if (cmp > 0)
        return procuraArvore(raiz->left, nome);
    if (cmp < 0)
        return procuraArvore(raiz->right, nome);

    return 0;
}

//destruo a árvore de forma recursiva
void destroiArvore(No **ppNo) {
    if (!ppNo || !*ppNo)
        return;

    destroiArvore(&(*ppNo)->left);
    destroiArvore(&(*ppNo)->right);
    free(*ppNo);
    *ppNo = NULL;
}

//remove a pilha seguindo a lógica do LIFO
void removePilha(PilhaExecucao *pPilha){

    if (!pPilha || !pPilha->topo) {
        printf("Escopo nao aberto\n");
        return;
    }

    Escopo *rem = pPilha->topo;
    pPilha->topo = rem->next;
    destroiArvore(&rem->raiz);
    // eu não dou free(rem->next), senão eu estaria liberando o próximo nó
    //Além disso, eu mantive acesso ao nó original
    free(rem);
    pPilha->n--;

}

int executar(const char *nomeArquivo, PilhaExecucao* pPilha) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Não foi possível abrir o arquivo.\n");
        return 0;
    }

    int code;
    //lê o arquivo inteiro
    while ((code = lePalavras(file)) != EOF){

        switch (code) {
            // begin
            case 1:
                //Se for beguin adiciona uma nova pilha
                if (pPilha)
                    adicionaPilha(pPilha);

                break;
            // end
            case 2:
                //objetivo aqui é quando receber o end ocorrerá a remoção da última árvore
                removePilha(pPilha);

                break;
            // var
            case 3:
                // le a chave, o valor e adiciona na arvore da pilha atual
                leValor(file, pPilha);

                break;
            // print
            case 4:
                //se nao conseguir imprimir(ou seja, não achou) retorna 1, encerrando o programa. A mensagem de erro está na função
                if (!imprimir(file, pPilha))
                    return 1;

                break;
        }

    };
    return 0;
    fclose(file);
}

// lê uma palavra no arquivo e retorna um dado valor com base na palavra. isso se deve ao switch nao lidar com strings.
int lePalavras(FILE *file) {
    char palavra[TAM];
    if (fscanf(file, "%s", palavra) == EOF)
        return EOF;

    if (strcmp(palavra, "begin") == 0)
        return 1;
    if (strcmp(palavra, "end") == 0)
        return 2;
    if (strcmp(palavra, "var") == 0)
        return 3;
    if (strcmp(palavra, "print") == 0)
        return 4;
    return 0;
}

//Lê var x = 10 e já adiciona na pilha atual
void leValor(FILE *file, PilhaExecucao *pPilha){

    if (!pPilha || !pPilha->topo) {
        printf("Erro: var fora de escopo (faltou begin)\n");
        return;
    }
    char nome[TAM], igual, valor[TAM];

    fscanf(file, "%s %c %s", nome, &igual, valor);

    Registro reg;
    strcpy(reg.nome, nome);
    strcpy(reg.valor, valor);

    No *novo = noCria(reg);

    adicionarNaArvore(pPilha, novo);
}

// procura nas árvores para imprimir
int imprimir(FILE *file, PilhaExecucao *pPilha){
    char nome[TAM];

    fscanf(file, "%s", nome);
    int resp;
    Escopo *escop = pPilha->topo;
    // passa por todas as árvores caso não ache na primeira
    while (escop != NULL) {
        resp = procuraArvore(escop->raiz, nome);

        if (resp == 1)
            return 1;

        escop = escop->next;
    }

    printf("Variavel %s nao declarada\n", nome);
    return 0;
}