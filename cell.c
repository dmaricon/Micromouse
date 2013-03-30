/* File	:	cell.c			*
 * By	:	Daniel Mariconda	*/

/*	Functions for Cell struct	*/

#include "cell.h"

/* Initialization */
void c_init(Cell *c, int w, int cx, int cy)
{
	c->walls = w;
	c->dist = 255;
	c->x = cx;
	c->y = cy;
	c->checked = 0;
	c->visited = 0;
}
void c_clear(Cell *c)
{
	c->walls = NONE;
	c->dist = 255;
	c->x = 0;
	c->y = 0;
	c->checked = 0;
	c->visited = 0;
}
void clearWalls(Cell *c)
{
	c->walls = NONE;
}
void clearDist(Cell *c)
{
	c->dist = 255;
	c->checked = 0;
}
void copy(Cell *dest, Cell *source)
{
	dest->walls = source->walls;
	dest->dist = source->dist;
	dest->x = source->x;
	dest->y = source->y;
	dest->checked = 0;
	dest->visited = 0;
}

/* Access */
int getWalls(Cell *c)
{
	return c->walls;
}
int getDist(Cell *c)
{
	return c->dist;
}
int getx(Cell *c)
{
	return c->x;
}
int gety(Cell *c)
{
	return c->y;
}
int hasEast(Cell *c)
{
	return(getWalls(c)==E || getWalls(c)==NE);
}
int hasNorth(Cell *c)
{
	return(getWalls(c)==N || getWalls(c)==NE);
}
int c_checked(Cell *c)
{
	return c->checked;
}
int visited(Cell *c)
{
	return c->visited;
}

/* Modification */
void setWalls(Cell *c, int w)
{
	c->walls = w;
}
void addWall(Cell *c, int w)
{
	c->walls += w;
}
void setDist(Cell *c, int d)
{
	c->dist = d;
}
