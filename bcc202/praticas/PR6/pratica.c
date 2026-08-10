#include <stdio.h>
#include "aluno.h"

int main() {
    Dicionario d;
    int n;
    scanf("%d", &n);

    char palavra[100];
    char definicao[100];

    d.tam = 0;
    for (int i = 0; i < n; i++) {
        scanf(" %s", palavra);
        fgets(definicao, 100, stdin);

        insereDicionario(&d, palavra, definicao);
    }

    char chave[100];
    scanf("%s", chave);

    ShellSort(d.itens, d.tam);
    int pos = buscaBinaria(d, chave);

    if (pos == -1)
        printf("Palavra não encontrada!\n");
    else {
        Elemento e = d.itens[pos];
        printf("%s: %s", e.palavra, e.definicao);
    }


    return 0;
}
