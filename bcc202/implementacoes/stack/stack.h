#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;
typedef struct item Item;

Stack *createStack();
void freeStack(Stack **stack);
void stackPush(Stack *stack, int val);
int stackPop(Stack *stack);
void stackPrint(Stack *stack);

#endif
