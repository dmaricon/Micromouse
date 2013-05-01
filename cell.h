/* File	:	cell.h			*
 * By	:	Daniel Mariconda	*/

/*	Header file for cell.c		*/

#ifndef CELL_H
#define CELL_H

typedef struct {
	int walls; //presence(?) of north and east walls
	int dist; //distance from destination cell
	int x,y; //cell location
	int checked; //flag used for solving algorithm
	int visited; //possible flag for maze exploration
} Cell;

//values for "walls" field
#define NONE 0
#define N 1
#define E 2
#define NE 3

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
int checked(Cell *c);
int visited(Cell *c);
/* Modification */
void setWalls(Cell *c, int w);
void addWall(Cell *c, int w);
void setDist(Cell *c, int d);
void visit(Cell* c);

#endif
