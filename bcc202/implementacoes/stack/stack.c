#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct item {
    int val;
    struct item *next;
};

struct stack {
    Item *top;
    size_t size;
};

Stack* createStack() {
    Stack *stack = (Stack* ) malloc(sizeof(Stack));
    if (stack) {
        stack->size = 0;
        stack->top = (Item *) malloc(sizeof(Item));
        if (!stack->top) {
            free(stack);
            return NULL;
        }
    }

    return stack;
}

void stackPush(Stack *stack, int val) {
    if (!stack)
        return;

    Item *aux = (Item *) malloc(sizeof(Item));
    if (!aux)
        return;

    aux->val = val;
    aux->next = stack->top->next;
    stack->top->next = aux;
    stack->size++;
}

int stackPop(Stack *stack) {
    int pop;
    if (!stack || stack->size == 0) 
        return -1;
    
    if (stack->size == 1) {
        pop = stack->top->next->val;
        stack->top->next = NULL;
        stack->size--;
        return pop;
    }

    pop = stack->top->next->val;
    stack->top->next = stack->top->next->next; 

    stack->size--;
    return pop;
}

void stackPrint(Stack *stack) {
    if (!stack)
        return;

    printf("[ ");
    Item* temp = stack->top;
    while (temp->next) {
        printf("%d ", temp->next->val);
        temp = temp->next; 
    }
    printf("]\n");
}

void freeStack(Stack **stack) {
    if (*stack) {
        Stack *s = *stack;
    
        Item *current = s->top;
    
        while (current != NULL) {
            Item *next = current->next; 
            free(current);              
            current = next;             
        }

        free(s);
        *stack = NULL;
    }  
}
