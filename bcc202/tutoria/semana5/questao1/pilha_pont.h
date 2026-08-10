#ifndef PILHA_PONT_H
#define PILHA_PONT_H

typedef struct pilha Pilha;
typedef struct celula Celula;

Pilha* criaPilhaPont();
int pilhaEhVaziaPont(Pilha *p);
void pilhaPushPont(Pilha *p, int val);
int pilhaPopPont(Pilha *p);
void freePilhaPont(Pilha **p);
void printPilhaPont(Pilha* p);

#endif
