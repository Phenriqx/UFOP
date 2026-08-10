#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

int main(){
    Estoque *e = criaEstoque();

    char nome[MAX], tipo[MAX];
    int pc;

    while (1) {
        if(scanf("%s", nome) == EOF) 
            break;
        if (!strcmp(nome, "0"))
            break;

        scanf("%s %d", tipo, &pc);

        if (e->tamanho >= e->capacidade) {
            e->capacidade *= 2;
            Pokemon *temp = (Pokemon *)realloc(e->estoque, e->capacidade * sizeof(Pokemon));
            if (!temp) {
                printf("Erro ao realocar memória\n");
                return 1;
            }

            e->estoque = temp;
        }
        
        strcpy(e->estoque[e->tamanho].nome, nome);
        strcpy(e->estoque[e->tamanho].tipo, tipo);
        e->estoque[e->tamanho].pc = pc;
        
        e->tamanho++;
    }

    printf("\nMaior PC por tipo:\n");
    mostrarMaioresPorTipo(e);

    printf("\nRepetidos:\n");
    mostrarRepetidos(e);

    liberarEstoque(&e); 

    return 0;
}
