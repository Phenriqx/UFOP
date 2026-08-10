#include <stdio.h>
#include <stdlib.h>

#include "aluno.h"

MapaCidades* criaMapa(int n, int m) {
    MapaCidades *mapa = (MapaCidades *)malloc(sizeof(MapaCidades));
    if (!mapa)
        return NULL;

    mapa->qtd = n;
    mapa->vector = malloc(n * sizeof(Node *));
    if (!mapa->vector) {
        free(mapa);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        mapa->vector[i] = NULL;

    // lendo as conexões
    int origem, destino;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &origem, &destino);

        Node *node = (Node *)malloc(sizeof(Node));
        if (!node)
            return NULL;

        node->destino = destino;
        node->prox = mapa->vector[origem];
        mapa->vector[origem] = node;
    }

    return mapa;
}

void liberaMapa(MapaCidades **m) {
    if (!(*m))
        return;

    for (int i = 0; i < (*m)->qtd; i++) {
        Node *aux = (*m)->vector[i];
        while (aux) {
            Node *temp = aux;
            aux = aux->prox;
            free(temp);
        }
    }

    free((*m)->vector);
    free(*m);
    *m = NULL;
}

int existeCaminho(MapaCidades *m, int origem, int destino, int *visitado) {
    if (origem == destino)
        return 1;

    visitado[origem] = 1;

    Node *node = m->vector[origem];
    while (node) {
        if (!visitado[node->destino]) {
            if (existeCaminho(m, node->destino, destino, visitado))
                return 1;
        }

        node = node->prox;
    }

    return 0;
}

int chamaCaminho(MapaCidades *m) {
    int origem, destino;
    if (scanf("%d %d", &origem, &destino) != 2) 
        return 0;  
    
    int *visitado = malloc(sizeof(int) * m->qtd);
    if (!visitado)
        return 0;

    for (int i = 0; i < m->qtd; i++)
        visitado[i] = 0;
    
    int existe = existeCaminho(m, origem, destino, visitado);
    free(visitado);

    return existe;
}