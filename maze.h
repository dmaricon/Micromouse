/* File	:	maze.h			*
 * By	:	Daniel Mariconda	*/

/*	Header file for maze.c	*/

#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

/* Initialization */
void m_init(Cell maze[][16]);
/* Utilities */
int isValid(int x, int y);	/* Checks if (x,y) is within the maze */
int openNorth(Cell maze[][16], int x, int y);
int openEast(Cell maze[][16], int x, int y);
int openSouth(Cell maze[][16], int x, int y);
int openWest(Cell maze[][16], int x, int y);
void addFWall(Cell maze[][16], int x, int y, int dir);
void addRWall(Cell maze[][16], int x, int y, int dir);
void addLWall(Cell maze[][16], int x, int y, int dir);

#endif
