#include "stack.h"
#include "cell.h"
#include <stdio.h>

/* Initialization */
void s_init(Stack *s)
{ s->count = 0; }
void s_clear(Stack *s)
{ s->count = 0; }

/* Operations */
void push(Stack *s, Entry e)
{
	s->contents[s->count] = e;
	s->count++;
}
Entry pop(Stack *s)
{
	if(s_empty(s)){
		printf("WARNING: Popping from empty stack!\n");
		return s->contents[0];
	}
	else {
		s->count--;
		return s->contents[s->count];
	}
}
int s_empty(Stack *s)
{ return(s->count==0); }
/*void display(Stack *s)
{
	int i;
	printf("Stack contents:\n");
	for(i=s->count-1;i>=0;i--)
		printf("%d\n",s->contents[i]);
}
*/
