/* File	:	maze.h			*
 * By	:	Daniel Mariconda	*/

/*	Header file for maze.c	*/

#ifndef MAZE_H
#define MAZE_H

#define TEST

#include "cell.h"

#ifdef TEST
#include "stack.h"
#include <time.h>
#endif

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

/* Initialization */
void m_init(Cell maze[][16]);
/* Utilities */
int xyWalls(Cell maze[][16], int x, int y);	/* Gets walls of cell (x,y) */
int isValid(int x, int y);	/* Checks if (x,y) is within the maze */
int openNorth(Cell maze[][16], int x, int y);
int openEast(Cell maze[][16], int x, int y);
int openSouth(Cell maze[][16], int x, int y);
int openWest(Cell maze[][16], int x, int y);
void addFWall(Cell maze[][16], int x, int y, int dir);
void addRWall(Cell maze[][16], int x, int y, int dir);
void addLWall(Cell maze[][16], int x, int y, int dir);

#ifdef TEST
/* Test functions */
void generateBinary(Cell maze[][16]); /* Generates a binary maze */
void generateDFS(Cell maze[][16]); /* Generates a depth-first-search maze */
void display(Cell maze[][16], int mx, int my);	/* Displays the maze */
void printBorder();			/* Prints a maze border (top/bottom) */
void showDirection(int dir);
/*int has4Walls(Cell maze[][16], int x, int y);*/
#endif

#endif
