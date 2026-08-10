#ifndef PILHA_VEC_H
#define PILHA_VEC_H

typedef struct pilha Pilha;

Pilha* criaPilha();
int pilhaEhVazia(Pilha *p);
void pilhaPush(Pilha *p, int val);
int pilhaPop(Pilha *p);
void freePilha(Pilha **p);
void printPilha(Pilha* p);

#endif
