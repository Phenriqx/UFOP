#ifndef LIST_H
#define LIST_H

typedef struct node Node;
typedef struct list List;

List* createList();
void insertList(List *list, int val);
void tradePositions(List* list, int idx);
void printList(List* list);

#endif
