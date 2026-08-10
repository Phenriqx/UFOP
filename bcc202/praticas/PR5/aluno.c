#include <stdlib.h>
#include <stdio.h>

#include "aluno.h"

struct peca {
    char tipo;
    int id, lote;
    float preco, peso;
};

struct pecas {
    Peca* vet;
    int n;
};

void troca(Peca *a, Peca *b);
int compararPecas(Peca p1, Peca p2);
void quickrec(Peca *v, int p, int r); 
int partition(Peca *v, int p, int r); 

Pecas* criaPecas(int n) {
	Pecas* pecas = (Pecas *) malloc(sizeof(Pecas));
	if (pecas) {
		pecas->n = n;
		pecas->vet = (Peca*) malloc(sizeof(Peca) * n);
		if (!pecas->vet) {
			free(pecas);
			return NULL;
		}
	}

	return pecas;
}

void freePecas(Pecas **pecas) {
  if (!*pecas || !pecas)
	  return;

    free((*pecas)->vet);
    free(*pecas);
    *pecas = NULL;
}

void lerInput(Pecas *pecas) {
    for (int i = 0; i < pecas->n; i++) 
	scanf(" %c %d %d %f %f", &pecas->vet[i].tipo, &pecas->vet[i].id, &pecas->vet[i].lote, &pecas->vet[i].preco, &pecas->vet[i].peso);		
}

void QuickSort(Peca *v, int n) {
    if (n > 0)
        quickrec(v, 0, n - 1);
}

void quickrec(Peca *v, int p, int r) {
    if (p < r) {
        int q = partition(v, p, r);
        quickrec(v, p, q - 1);
        quickrec(v, q + 1, r);
    }
}

void ordenaPecas(Pecas *pecas) {
	Peca *A = malloc(sizeof(Peca) * pecas->n);
    Peca *B = malloc(sizeof(Peca) * pecas->n);
    Peca *C = malloc(sizeof(Peca) * pecas->n);
    int nA = 0, nB = 0, nC = 0;

    for (int i = 0; i < pecas->n; i++) {
        if (pecas->vet[i].tipo == 'A') 
			A[nA++] = pecas->vet[i];
        else if (pecas->vet[i].tipo == 'B') 
			B[nB++] = pecas->vet[i];
        else if (pecas->vet[i].tipo == 'C') 
			C[nC++] = pecas->vet[i];
    }

    QuickSort(A, nA);
    QuickSort(B, nB);
    QuickSort(C, nC);

    printf("Tipo A:");
    for (int i = 0; i < nA; i++) 
		printf(" %03d", A[i].id);

    printf("\nTipo B:");
    for (int i = 0; i < nB; i++) 
		printf(" %03d", B[i].id);

    printf("\nTipo C:");
    for (int i = 0; i < nC; i++) 
		printf(" %03d", C[i].id);

    printf("\n");

    free(A); 
	free(B); 
	free(C);
}

int compararPecas(Peca p1, Peca p2) {
    if (p1.tipo == 'A') {
        if (p1.peso < p2.peso) 
			return -1;
        if (p1.peso > p2.peso) 
			return 1;
    } else if (p1.tipo == 'B') {
        if (p1.preco < p2.preco) 
			return -1;
        if (p1.preco > p2.preco) 
			return 1;
    } else if (p1.tipo == 'C') {
        if (p1.lote < p2.lote) 
			return -1;
        if (p1.lote > p2.lote) 
			return 1;
    }

    if (p1.lote != p2.lote) {
		if (p1.lote < p2.lote) return -1;
		else return 1;
	}
    if (p1.peso != p2.peso) {
		if (p1.peso < p2.peso) return -1;
		else return 1;
	}
    if (p1.preco != p2.preco) {
		if (p1.preco < p2.preco) return -1;
		else return 1;
	}

    return 0;
}

void troca(Peca *a, Peca *b) {
    Peca temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Peca *v, int p, int r) {
    Peca x = v[r]; // Pivô
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        int resultado = compararPecas(v[j], x);
        if (resultado <= 0) {
            i++;
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[i + 1], &v[r]);
    return i + 1;
}
