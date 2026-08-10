#include <stdio.h>

#include "array.h"

int main() {
    Array *array = createArray();

    for (int i = 0; i < 5; i++)
        appendArray(array, i + 1);

    printArray(array);
    insertAtPos(array, 0, 0);

    printArray(array);

    removeAtPos(array, 5);
    printArray(array);

    freeArray(&array);
    return 0;
}