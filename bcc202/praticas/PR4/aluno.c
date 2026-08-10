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

int existeCaminho(MapaCidades *m, int origem, int destino) {
    if (origem == destino)
        return 1;

    int visitado[m->qtd];
    for (int i = 0; i < m->qtd; i++) 
        visitado[i] = 0;
    
    int fila[m->qtd];
    int front = 0, rear = 0;

    visitado[origem] = 1; // marca origem como visitado
    fila[rear] = origem; // adiciona origem na fila de processamento

    rear = (rear + 1) % m->qtd;

    while (front != rear) {
        int current = fila[front];
        front = (front + 1) % m->qtd;
        if (current == destino)
            return 1;

        Node* adj = m->vector[current];
        while (adj != NULL) {
            if (!visitado[adj->destino]) {
                visitado[adj->destino] = 1;

                fila[rear] = adj->destino;
                rear = (rear + 1) % m->qtd;
            }

            adj = adj->prox;
        }
    }

    return 0;
}

int chamaCaminho(MapaCidades *m) {
    int origem, destino;
    if (scanf("%d %d", &origem, &destino) != 2) 
        return 0;  
    
    int existe = existeCaminho(m, origem, destino);

    return existe;
}
