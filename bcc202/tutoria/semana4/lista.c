#include <stdio.h>
#include <stdlib.h>

struct celula {
    int val;
    struct celula *next;
}; 
typedef struct celula Celula;

typedef struct {
    int val;
    Celula *head;
    Celula *tail;
} Lista;

void inverter(Lista *l) {
    if (!l->head) return;

    Celula *prev = NULL;
    Celula *cur = l->head;
    Celula *next;

    l->tail = l->head;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    l->head = prev;
}

void removeDuplicados(Lista *l) {
    Celula *cur = l->head;

    while (cur) {
        Celula *runner = cur;
        while (runner->next) {
            if (runner->next->val == cur->val) {
                Celula *tmp = runner->next;
                runner->next = tmp->next;

                if (tmp == l->tail)
                    l->tail = runner;

                free(tmp);
            } else {
                runner = runner->next;
            }
        }
        cur = cur->next;
    }
}

void concat(Lista *l1, Lista *l2) {
    if (!l1->head) {
        *l1 = *l2;
        return;
    }

    if (!l2->head) return;

    l1->tail->next = l2->head;
    l1->tail = l2->tail;
}

int removeValue(int arr[], int size, int val) {
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != val) {
            arr[j++] = arr[i];
        }
    }
    return j;
}

Celula* newNode(int v) {
    Celula *n = (Celula*) malloc(sizeof(Celula));
    n->val = v;
    n->next = NULL;
    return n;
}

void push(Lista *l, int v) {
    Celula *n = newNode(v);
    if (!l->head) {
        l->head = l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
}

void print(Lista *l) {
    Celula *p = l->head;
    while (p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main() {

    Lista l = {0, NULL, NULL};
    push(&l, 1);
    push(&l, 2);
    push(&l, 2);
    push(&l, 3);
    push(&l, 4);
    push(&l, 4);

    printf("Lista original: ");
    print(&l);

    removeDuplicados(&l);
    printf("Sem duplicados: ");
    print(&l);

    inverter(&l);
    printf("Invertida: ");
    print(&l);

    Lista l2 = {0, NULL, NULL};
    push(&l2, 9);
    push(&l2, 10);

    concat(&l, &l2);
    printf("Concatenada: ");
    print(&l);

    int arr[] = {2,5,2,8,2,9};
    int novoTam = removeValue(arr, 6, 2);

    printf("Array sem 2: ");
    for (int i = 0; i < novoTam; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
