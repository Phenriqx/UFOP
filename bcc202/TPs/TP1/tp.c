#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

int main() {
    int n, m;

    scanf("%d %d", &n, &m);
    Formula *formula = criaFormula(n, m);

    int *vet = malloc(n * sizeof(int));
    int *vetAux = malloc(n * sizeof(int));


    for(int i = 0; i < n; i++){
        vet[i] = 1;
        vetAux[i] = i + 1;
    }

    adicionaClausula(formula);

    if (solucaoFormula(formula, 0, vet, vetAux)) {
        printf("Fórmula:");
        imprimeFormula(formula);

        printf("Solução encontrada:\n");
        for (int i = 0; i < n; i++) {
            if (vet[i] == 1) 
                printf("%c:  True\n", intToChar(i + 1));
            else
                printf("%c:  False\n", intToChar(i + 1));
        }
    }
    else 
        printf("Fórmula insatisfazível!\n");
    
    destroiFormula(formula);
    
    free(vet);
    free(vetAux);

    return 0;
}
