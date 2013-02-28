#ifndef STACK_H
#define STACK_H

#include "cell.h"

#define STACKSIZE 256
typedef Cell * Entry;

typedef struct {
	Entry contents [STACKSIZE];
	int count;
} Stack;

/* Initialization */
void s_init(Stack *s);
void s_clear(Stack *s);

/* Operations */
void push(Stack *s, Entry e);
Entry pop(Stack *s);

int s_empty(Stack *s);
/*void display(Stack *s);*/

#endif
