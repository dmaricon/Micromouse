/* File	:	queue.h			*
 * By	:	Daniel Mariconda	*/

/*	Header file for queue.c		*/

#ifndef QUEUE_H
#define QUEUE_H

#include "cell.h"

#define QSIZE 256

typedef struct {
	Cell* contents[QSIZE];
	int front;
	int count;
} Queue;

/* Initialization */
void q_init(Queue *q);		/* These two functions do the same thing */
void q_clear(Queue *q);

/* Operations */
void in(Queue *q, Cell *c);	/* Adds a cell dist to the back of the queue */
void out(Queue *q);
int frontx(Queue *q);
int fronty(Queue *q);
Cell * qfront(Queue *q);		/* Returns a pointer to the front element */
int getFront(Queue *q);

int empty(Queue *q);

#endif
