#include <stdlib.h>

#include "stack.h"

struct node {
	char val;
	struct node *prox;
};

struct stack {
	Node* topo;
	size_t size;
};

Stack* criaPilha() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack) {
        stack->size = 0;
        stack->topo = (Node *) malloc(sizeof(Node));
        if (!stack->topo) {
            free(stack);
            return NULL;
        }
    }

    return stack;
}

void stackPush(Stack *stack, char val) {
    if (!stack)
        return;

    
}