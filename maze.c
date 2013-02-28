/* File	:	maze.c			*
 * By	:	Daniel Mariconda	*/

/*	Maze-related functions	*/

#include <stdio.h>
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
int xyWalls(Cell maze[][16], int x, int y)
{
	return getWalls(&maze[x][y]);
}
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

#ifdef TEST
/* Test functions */
void generateBinary(Cell maze[][16])
{
	srand(time(0));
	int x, y;
	for(x=0;x<15;x++)
		for(y=0;y<15;y++){
			if(rand()%2)
				setWalls(&maze[x][y],N);
			else
				setWalls(&maze[x][y],E);
		}
	setWalls(&maze[0][0],E);
}
void generateDFS(Cell maze[][16])
{
	Stack s;
	int total = 251;
	int visits = 0;
	Cell * current;
	s_init(&s);
	int r,x,y;
	int found=0;

	for(x=0;x<16;x++)
		for(y=0;y<16;y++)
			setWalls(&maze[x][y],NE);
		
	

	r=rand()%4;
	switch(r){
		case 0:	current = &maze[7][7];
			break;
		case 1:	current = &maze[8][7];
			break;
		case 2:	current = &maze[7][8];
			break;
		case 3:	current = &maze[8][8];
			break;
	}

	while(visits<total){
		r=rand()%4;
		while(!found){
			x=getx(current);
			y=gety(current);
			switch(r){
				case 0:	if(isValid(x,y+1))
						if(!visited(&maze[x][y+1])){
							
						}
					break;
			}
		}
		visits++;
	}
}
void display(Cell maze[][16], int mx, int my)
{
	int x, y;

	printBorder();

	for(y=15;y>=0;y--){
		printf("|");
		for(x=0;x<16;x++){
			if(x==mx&&y==my)
				printf("@-@");
			else{
				if(getDist(&maze[x][y])==255)
					printf("   ");
				else if(getDist(&maze[x][y])<10)
					printf(" %d ",getDist(&maze[x][y]));
				else if (getDist(&maze[x][y])<100)
					printf(" %d",getDist(&maze[x][y]));
				else
					printf("%d",getDist(&maze[x][y]));
			}
			if(isValid(x+1,y)){
				if(hasEast(&maze[x][y]))
					printf("|");
				else
					printf(" ");
			}
		}
		printf("|\n+");
		for(x=0;x<16;x++){
			if(isValid(x,y-1) && !hasNorth(&maze[x][y-1]))
				printf("   ");
			else
				printf("---");
			printf("+");
		}
		printf("\n");
	}
}

void printBorder()
{
	int i;
	for(i=0;i<16;i++)printf("+---");
	printf("+\n");
}

void showDirection(int dir)
{
	printf("Facing ");
	switch(dir){
		case NORTH:	printf("north\n");
				break;
		case EAST:	printf("east\n");
				break;
		case SOUTH:	printf("south\n");
				break;
		case WEST:	printf("west\n");
				break;
	}
}
/*int has4Walls(Cell maze[][16], int x, int y)
{
	return!(openNorth(maze,x,y)||openEast(maze,x,y)||openSouth(maze,x,y)
			||openWest(maze,x,y));
}*/
#endif
