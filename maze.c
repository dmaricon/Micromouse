/* File	:	maze.c			*
 * By	:	Daniel Mariconda	*/

/*	Maze-related functions	*/

#include <stdlib.h>
#include "maze.h"

/* Initialization */
void m_init(Cell maze[][16])
{
	int x,y;
	for(x=0;x<16;x++){
		for(y=0;y<16;y++){
			c_init(&maze[x][y],0,x,y);
		}
	}
}

/* Utilities */
int isValid(int x, int y)
{
	return(x>=0 && x<16 && y>=0 && y<16);
}
int openNorth(Cell maze[][16], int x, int y)
{
	if(!isValid(x,y+1))
		return 0;
	return(!hasNorth(&maze[x][y]));
}
int openEast(Cell maze[][16], int x, int y)
{
	if(!isValid(x+1,y))
		return 0;
	return(!hasEast(&maze[x][y]));
}
int openSouth(Cell maze[][16], int x, int y)
{
	if(!isValid(x,y-1))
		return 0;
	return(!hasNorth(&maze[x][y-1]));
}
int openWest(Cell maze[][16], int x, int y)
{
	if(!isValid(x-1,y))
		return 0;
	return(!hasEast(&maze[x-1][y]));
}
void addFWall(Cell maze[][16], int x, int y, int dir)
{
	switch(dir){
		case NORTH:
			if(isValid(x,y+1)&&!hasNorth(&maze[x][y]))
				addWall(&maze[x][y],N);
			break;
		case EAST:
			if(isValid(x+1,y)&&!hasEast(&maze[x][y]))
				addWall(&maze[x][y],E);
			break;
		case SOUTH:
			if(isValid(x,y-1))
				if(!hasNorth(&maze[x][y-1]))
					addWall(&maze[x][y-1],N);
			break;
		case WEST:
			if(isValid(x-1,y))
				if(!hasEast(&maze[x-1][y]))
					addWall(&maze[x-1][y],E);
			break;
	}
}
void addRWall(Cell maze[][16], int x, int y, int dir)
{
	switch(dir){
		case WEST:
			if(isValid(x,y+1)&&!hasNorth(&maze[x][y]))
				addWall(&maze[x][y],N);
			break;
		case NORTH:
			if(isValid(x+1,y)&&!hasEast(&maze[x][y]))
				addWall(&maze[x][y],E);
			break;
		case EAST:
			if(isValid(x,y-1))
				if(!hasNorth(&maze[x][y-1]))
					addWall(&maze[x][y-1],N);
			break;
		case SOUTH:
			if(isValid(x-1,y))
				if(!hasEast(&maze[x-1][y]))
					addWall(&maze[x-1][y],E);
			break;
	}
}

void addLWall(Cell maze[][16], int x, int y, int dir)
{
	switch(dir){
		case EAST:
			if(isValid(x,y+1)&&!hasNorth(&maze[x][y]))
				addWall(&maze[x][y],N);
			break;
		case SOUTH:
			if(isValid(x+1,y)&&!hasEast(&maze[x][y]))
				addWall(&maze[x][y],E);
			break;
		case WEST:
			if(isValid(x,y-1))
				if(!hasNorth(&maze[x][y-1]))
					addWall(&maze[x][y-1],N);
			break;
		case NORTH:
			if(isValid(x-1,y))
				if(!hasEast(&maze[x-1][y]))
					addWall(&maze[x-1][y],E);
			break;
	}
}
