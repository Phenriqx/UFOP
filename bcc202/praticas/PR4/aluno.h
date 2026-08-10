#ifndef ALUNO_H
#define ALUNO_H

typedef struct Node {
    int destino; 
    struct Node *prox;
} Node;

typedef struct {
    Node **vector; 
    int qtd;
} MapaCidades;

MapaCidades* criaMapa(int n, int m);
void liberaMapa(MapaCidades **m);
int existeCaminho(MapaCidades *m, int origem, int destino);
int chamaCaminho(MapaCidades *m); // Chama a função existeCaminho

#endif