#include <stdio.h>
#include "filaprocessos.h"

int main(){
    int n;
    scanf("%d", &n);
    FilaProcessos* fila = criaFila(n);

    for (int i = 0; i < n; i++)
        adicionaFila(fila, i);

    printf("\nLog CPU: \n");
    escalonador(fila);

    destroiFila(&fila);

    return 0;
}
