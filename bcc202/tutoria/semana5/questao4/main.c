#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

int main() {
	Fila* f = criarFila();

    Aluno* a1 = criaAluno(101, "Joao Silva");
    insertFila(f, a1);
    free(a1); 

    Aluno* a2 = criaAluno(102, "Maria Oliveira");
    insertFila(f, a2);
    free(a2);

    Aluno* a3 = criaAluno(103, "Carlos Santos");
    insertFila(f, a3);
    free(a3);

    printFila(f);


    int matricula_removida = popFila(f);
    printf("Aluno removido (Matricula): %d\n", matricula_removida);
    
    printFila(f); 

    while(1) {
        int mat = popFila(f);
        if (mat == -1)
            break;
        
        printf("Removendo aluno mat: %d\n", mat);
    }

    freeFila(&f);
    return 0;
}
