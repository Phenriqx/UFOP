#include <stdio.h>

#include "tree.h"

int main() {
    No *pNo;
    ArvoreInicia(&pNo);

    printf("Inseriu (3|lara): %s\n", ArvoreInsere(&pNo, (Registro){3, "lara"}) ? "sim" : "nao");
    printf("Inseriu (5|gustavo): %s\n", ArvoreInsere(&pNo, (Registro){5, "gustavo"}) ? "sim" : "nao");
    printf("Inseriu (4|pedro): %s\n", ArvoreInsere(&pNo, (Registro){4, "pedro"}) ? "sim" : "nao");
    printf("Inseriu (2|jorge): %s\n", ArvoreInsere(&pNo, (Registro){2, "jorge"}) ? "sim" : "nao");
    printf("Inseriu (1|regina): %s\n", ArvoreInsere(&pNo, (Registro){1, "regina"}) ? "sim" : "nao");
    printf("Inseriu (7|chica): %s\n", ArvoreInsere(&pNo, (Registro){7, "chica"}) ? "sim" : "nao");


    Registro reg;
    Chave chave = 5;
    bool resp = ArvorePesquisa(pNo, chave, &reg);
    if (resp) {
        printf("No %d encontrado: ", chave);
        printRegistro(reg);
        printf("\n");
    } else
        printf("No %d nao encontrado!\n", chave);

    chave = 15;
    resp = ArvorePesquisa(pNo, chave, &reg);
    if (resp) {
        printf("No %d encontrado: ", chave);
        printRegistro(reg);
        printf("\n");
    } else {
        printf("No %d nao encontrado!\n", chave);
    }

    Caminhamento(pNo, POSTORDER);

    return 0;
}