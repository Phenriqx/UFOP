#include <stdio.h>

#include "lista.h"

int main() {
    Lista *l = createLinkedList();

    insertAtEnd(l, 1);
    insertAtEnd(l, 2);
    insertAtEnd(l, 3);
    insertAtEnd(l, 4);
    insertAtBeginning(l, 7);
    insertAtBeginning(l, 9);
	insertAtEnd(l, 0);
    
    // printf("soma dos elementos: %d\n", recursiveSum(l));
    printLinkedList(l);
    //listaInverteParte(l, 2);
    //printLinkedList(l);

    moveMenor(l);
    printLinkedList(l);

    // printLinkedList(l);
    // bool res = insertAtBeginning(l, 10);
    // printLinkedList(l);
    // res = removeAtBeginning(l);
    // printLinkedList(l);
    // res = removeAtEnd(l);
    // printLinkedList(l);
    return 0;
}
