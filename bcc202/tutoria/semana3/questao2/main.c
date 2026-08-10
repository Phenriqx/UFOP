#include <stdio.h>

#include "tad.h"

int main() {
    int n;
    printf("Quantas cidades quer alocar? ");
    scanf("%d", &n);

    Cidade *cidades = alocarCidade(n);

    char nome[MAX];
    int qntHab, qntEscola;

    printf("Insira o nome, qnt de habitantes e qnt de escolas das %d cidades a seguir:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", nome, &qntHab, &qntEscola);

        adicionaCidade(cidades, nome, qntHab, qntEscola, i);
    }

    int maisEscolas = cidadeComMaisEscolas(cidades, n);
    printf("A cidade com mais escolas é: %s\n", getNomeCidade(cidades, maisEscolas));

    double totalHabitantes = calcularHabitantes(cidades, n);
    printf("O total de habitantes em todas as cidades é de: %.2lf milhões\n", totalHabitantes);

    int val;
    printf("Insira um valor (em milhões) para ver todas as cidades com população menor que esse valor: \n");
    scanf("%d", &val);

    imprimeCidadePequena(cidades, n, val);

    destroiCidade(&cidades);
    return 0;
}