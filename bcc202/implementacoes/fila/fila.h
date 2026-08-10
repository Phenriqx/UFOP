#ifndef FILA_H
#define FILA_H

typedef struct queue Queue;

Queue* createQueue();
void freeQueue(Queue **q);
void appendQueue(Queue* q, int val);
int popQueue(Queue* q);
void printQueue(Queue* q);
int sizeQueue(Queue* q);
Queue* filaIntercala(Queue *f1, Queue *f2);
Queue* inverteFila(Queue* q);
int isQueueEmpty(Queue* q);
void filhaEspelho(Queue* q);

#endif
