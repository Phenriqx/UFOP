#ifndef ALUNO_H
#define ALUNO_H

typedef struct peca Peca;
typedef struct pecas Pecas;

Pecas* criaPecas(int n);
void freePecas(Pecas **pecas);
void lerInput(Pecas* pecas);
void QuickSort(Peca *v, int n); 
void ordenaPecas(Pecas *pecas);

#endif
