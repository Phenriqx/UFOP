#include "stack.h"
#include <stdio.h>

int main() {
    Stack *stack = createStack();
    for (int i = 0; i < 5; i++)
        stackPush(stack, i + 1);

    stackPrint(stack);
    int pop = stackPop(stack);
    printf("pop: %d\n", pop);
    stackPrint(stack); 

    freeStack(&stack);
    return 0;
}
