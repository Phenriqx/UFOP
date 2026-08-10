#ifndef ARRAY_H
#define ARRAY_H

#define DEFAULT_CAPACITY 4

typedef struct item Item;
typedef struct array Array;
/*
O Array contém:
    Sua capacidade;
    Seu tamanho atual;
    Uma lista dos itens que ele contém (Item);
*/

Array *createArray();
void freeArray(Array **array);
void appendArray(Array *array, int val);
int popArray(Array *array);
void insertAtPos(Array *array, int value, int pos);
void removeAtPos(Array *array, int pos);

void printArray(Array *array);

#endif