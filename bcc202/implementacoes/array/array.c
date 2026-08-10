#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"

struct item {
    int val;
};

struct array {
    Item* item;
    size_t size;
    size_t capacity;
};

Array *createArray() {
    Array *array = (Array *)malloc(sizeof(Array));
    if (!array)
        return NULL;

    array->capacity = DEFAULT_CAPACITY;
    array->size = 0;

    array->item = malloc(sizeof(Item) * array->capacity);
    if (!array->item)
        return NULL;

    return array;
}

void freeArray(Array **array) {
    if ((*array)) {
        free((*array)->item);
        free((*array));
    }
}

void appendArray(Array *array, int val) { // O(1)
    if (array->size >= array->capacity) {
        array->capacity *= 2;
        Item *temp = (Item *)realloc(array->item, array->capacity * sizeof(Item));
        if (!temp) {
            array->capacity /= 2;
            return;
        }

        array->item = temp;
    }

    array->item[array->size].val = val;
    array->size++;
}

int popArray(Array *array) { // O(1)
    if (!array || array->size == 0) {
        printf("Error popping from the array\n");
        return 0;
    }

    int poppedItem = array->item[array->size - 1].val;
    array->size--;

    return poppedItem;
}

void printArray(Array* array) { // O(n)
    printf("[ ");
    for (int i = 0; i < array->size; i++) 
        printf("%d ", array->item[i].val);
    
    printf("]\n");
}

int getArray(Array *array, int pos) { // O(1)
    return array->item[pos].val;
}

void insertAtPos(Array *array, int value, int pos) {
    if (array->size >= array->capacity) {
        array->capacity *= 2;
        Item *temp = (Item *)realloc(array->item, array->capacity * sizeof(Item));
        if (!temp)
            return;

        array->item = temp;
        free(temp);
    }

    memmove(&array->item[pos + 1], &array->item[pos], (array->size - pos) * sizeof(Item));
    array->item[pos].val = value;
    array->size++;
}

void removeAtPos(Array* array, int pos) {
    for (int i = pos; i < array->size; i++)
        array->item[i].val = array->item[i + 1].val;

    array->size--;
}