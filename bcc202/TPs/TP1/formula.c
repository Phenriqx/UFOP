#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "formula.h"

struct clausula {
    int val[3];
    int valorLogico[3]; // 
};  

struct formula {
    Clausula* clausulas;
    int n, m;
};  

Formula* criaFormula(int n, int m) {
    Formula* formula = (Formula*) malloc(sizeof(Formula));
    if (!formula) {
        printf("Erro de alocação\n");
        return NULL;
    }

    formula->clausulas = malloc(m * sizeof(Clausula));
    if (!formula->clausulas) 
        return NULL;

    formula->n = n;
    formula->m = m;

    return formula;
}

void destroiFormula(Formula* f) {
    if (f->clausulas) {
        free(f->clausulas);
        f->clausulas = NULL;
    }

    free (f);
    f = NULL;
}

void adicionaClausula(Formula *f) {
    for (int i = 0; i < f->m; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &f->clausulas[i].val[j]);
            if(f->clausulas[i].val[j] < 0){
                f->clausulas[i].valorLogico[j] = 0;
                f->clausulas[i].val[j] *= -1;
            }else{
                f->clausulas[i].valorLogico[j] = 1;
            }
        }
    }
}

void imprimeFormula(Formula *f) {
    printf("\n");
    for (int i = 0; i < f->m; i++) {
        printf("( ");
        for (int j = 0; j < 3; j++) {
            if (f->clausulas[i].valorLogico[j] == 1)
                printf("%c ", intToChar(f->clausulas[i].val[j]));
            else 
                printf("~%c ", intToChar(f->clausulas[i].val[j]));
            if (j < 2)
                printf(" v ");
        }
        printf(" )");
        if (i < f->m - 1)
            printf(" ∧ ");
    }

    printf("\n");
}

int solucaoFormula(Formula *f, int n, int *vet, int *vetAux) {
    for(int i = 0; i < pow(2, f->n) -1; i++) {
        int saida = verificaCada(f, 0, vet, vetAux);

        if(saida == 1) {
            // for (int i = 0; i < f->n; i++) {
            //     f->clausulas[0].valorLogico[i] = vet[i];
            // }
            return 1;
            i = 8;
        }
        else {
            proxVeri(f, vet);
        }
    }
    return 0;
}

int verificaCada(Formula *f, int n, int *vet, int *vetAux) {
    if((f->m -1) == n)
        return verificaClausula(f, vet, n, vetAux);
    

    int saida = verificaCada(f, n +1, vet, vetAux);

    if (saida == 0) {
        return 0;
    }
    else {
        return verificaClausula(f, vet, n, vetAux);
    }
}

int verificaClausula(Formula *f, int *vet, int n, int *vetAux) {
    int vetClone[3];

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < f->n; j++){
            // Se os valores forem negativos
            if(vetAux[j] == f->clausulas[n].val[i]){
                vetClone[i] = vet[j];
            }
        }
        if(f->clausulas[n].valorLogico[i] == 0){
            vetClone[i] = !vetClone[i];
        }
    }

    int result = vetClone[0] | vetClone[1] | vetClone[2];

    return result;
}

void proxVeri(Formula *f, int *vet) {
    for(int j = (f->n -1); j >=0; j--) {
        vet[j] = !vet[j];

        if(vet[j] == 0) {
            break;
        }
    }
}


void limpaAdd(int *vet, int n){
    for(int i = 0; i < n; i++)
        vet[i] = 0;
}

char intToChar(int v) {
    return v + 'a' - 1;
}     
