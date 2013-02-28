/* File	:	queue.c			*
 * By	:	Daniel Mariconda	*/

/*	Contains functions for the Queue struct	*/

#include <stdio.h>
#include "cell.h"
#include "queue.h"

/* Initialization */
void q_init(Queue *q)
{
	q->front = 0;
	q->count = 0;
}
void q_clear(Queue *q)
{
	q_init(q);
}

/* Operations */
void in(Queue *q,Cell *c)
{
	c->checked = 1;
	q->contents[(q->front+q->count)%QSIZE]=c;
	q->count++;
}
void out(Queue *q)
{
	q->front=(q->front+1)%QSIZE;
	q->count--;
}
int frontx(Queue *q)
{
	Cell *temp;
	temp = qfront(q);
	return getx(temp);
}
int fronty(Queue *q)
{
	Cell *temp;
	temp = qfront(q);
	return gety(temp);
}
Cell * qfront(Queue *q)
{
	return q->contents[q->front];
}
int getFront(Queue *q)
{
	return q->front;
}
int empty(Queue *q)
{
	return (q->count==0);
}
