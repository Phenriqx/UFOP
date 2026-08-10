#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "aluno.h"

int main() {
    No* pNo;
    arvoreInicia(&pNo);

    char palavra[MAX];
    while (scanf("%s", palavra) != EOF) {

        // limpa pontuação no final da palavra
        int len = strlen(palavra);
        while (len > 0 && ispunct(palavra[len - 1])) {
            palavra[len - 1] = '\0';
            len--;
        }

        // converte para minúsculo
        for (int i = 0; palavra[i]; i++) {
            palavra[i] = tolower(palavra[i]);
        }

        // insere na árvore
        if (strlen(palavra) > 0) {
            Registro reg;
            strcpy(reg.palavra, palavra);
            reg.frequencia = 1;
            arvoreInsere(&pNo, reg);
        }
    }

    printInOrder(pNo);

    arvoreLibera(&pNo);
    return 0;
}