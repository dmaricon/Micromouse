/* File	:	cell.h			*
 * By	:	Daniel Mariconda	*/

/*	Header file for cell.c		*/

#ifndef CELL_H
#define CELL_H

#define NONE 0
#define N 1
#define E 2
#define NE 3

typedef struct {
	int walls;
	int dist;
	int x;
	int y;
	int checked;
	int visited;
} Cell;

/* Initialization */
void c_init(Cell *c, int w, int cx, int cy);
void c_clear(Cell *c);
void clearWalls(Cell *c);
void clearDist(Cell *c);
void copy(Cell *dest, Cell *source);
/* Access */
int getWalls(Cell *c);	/* Gets north / east walls of cell c */
int getDist(Cell *c);
int getx(Cell *c);
int gety(Cell *c);
int hasEast(Cell *c);
int hasNorth(Cell *c);
int c_checked(Cell *c);
int visited(Cell *c);
/* Modification */
void setWalls(Cell *c, int w);
void addWall(Cell *c, int w);
void setDist(Cell *c, int d);
/* Other */
/*
int xy2loc(int x, int y);
int locx(int l);
int locy(int l);
*/

#endif
