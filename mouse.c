#include "mouse.h"

void update(Cell maze[][16], int mx, int my, int dir, Cell testMaze[][16])
{
	if(seeFWall(mx,my,dir,testMaze)) addFWall(maze,mx,my,dir);
	if(seeRWall(mx,my,dir,testMaze)) addRWall(maze,mx,my,dir);
	if(seeLWall(mx,my,dir,testMaze)) addLWall(maze,mx,my,dir);
}
void flood(Cell maze[][16], Queue *q, int n)
{
	int d = 0;
	int x=0;
	int y=0;
	int n1 = n;
	int n2 = 0;

	while(!empty(q)){
		floodLevel(n1,d,q);
		d++;
		n2=n1;
		n1=0;
		for(;n2>0;n2--){    /* Check neighbors of each cell in queue */

			x=getx(qfront(q));
			y=gety(qfront(q));

			if(openNorth(maze,x,y) &&
			 getDist(&maze[x][y+1])==255 &&
			  !c_checked(&maze[x][y+1])){
				in(q,&maze[x][y+1]);
				n1++;
			}
			if(openEast(maze,x,y) &&
			 getDist(&maze[x+1][y])==255 &&
			  !c_checked(&maze[x+1][y])){
				in(q,&maze[x+1][y]);
				n1++;
			}
			if(openSouth(maze,x,y) &&
			 getDist(&maze[x][y-1])==255 &&
			  !c_checked(&maze[x][y-1])){
				in(q,&maze[x][y-1]);
				n1++;
			}
			if(openWest(maze,x,y) &&
			 getDist(&maze[x-1][y])==255 &&
			  !c_checked(&maze[x-1][y])){
				in(q,&maze[x-1][y]);
				n1++;
			}
			out(q);
		}
	}	
		
}

void floodLevel(int n, int d, Queue *q)
{
	int i;
	for(i=0;i<n;i++){
		setDist(q->contents[(getFront(q)+i)%QSIZE],d);
	}
}
void flood2center(Cell maze[][16])
{
	Queue q;
	int x=0;
	int y=0;
	q_init(&q);

	for(x=0;x<16;x++)
		for(y=0;y<16;y++)
			clearDist(&maze[x][y]);

	in(&q,&maze[7][8]);
	in(&q,&maze[8][8]);
	in(&q,&maze[7][7]);
	in(&q,&maze[8][7]);

	flood(maze,&q,4);
}
void flood2start(Cell maze[][16])
{
	Queue q;
	int x=0;
	int y=0;
	q_init(&q);

	for(x=0;x<16;x++)
		for(y=0;y<16;y++)
			clearDist(&maze[x][y]);

	in(&q,&maze[0][0]);

	flood(maze,&q,1);
}
void move(Cell maze[][16], int *mx, int *my, int *dir)
{
	if(goodFront(maze,*mx,*my,*dir)) go(mx,my,*dir);
	else if(goodRight(maze,*mx,*my,*dir)) goRight(mx,my,dir);
	else if(goodLeft(maze,*mx,*my,*dir)) goLeft(mx,my,dir);
	else goBack(mx,my,dir);
}

void turnRight(int *dir)
{
	*dir = (*dir+1)%4;
}

void turnLeft(int *dir)
{
	if(*dir==NORTH)*dir=WEST;
	else *dir=*dir-1;
}

void turnAround(int *dir)
{
	turnRight(dir);
	turnRight(dir);
}

void go(int *mx, int *my, int dir)
{
	switch(dir){
		case NORTH:
			*my=*my+1;
			break;
		case EAST:
			*mx=*mx+1;
			break;
		case SOUTH:
			*my=*my-1;
			break;
		case WEST:
			*mx=*mx-1;
			break;
	}
}

void goRight(int *mx, int *my, int *dir)
{
	turnRight(dir);
	go(mx,my,*dir);
}

void goLeft(int *mx, int *my, int *dir)
{
	turnLeft(dir);
	go(mx,my,*dir);
}

void goBack(int *mx, int *my, int *dir)
{
	turnAround(dir);
	go(mx,my,*dir);
}

int goodFront(Cell maze[][16], int mx, int my, int dir)
{
	switch(dir){
		case NORTH:
			return (openNorth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my+1]));
				break;
		case EAST:
			return (openEast(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx+1][my]));
				break;
		case SOUTH:
			return (openSouth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my-1]));
				break;
		case WEST:
			return (openWest(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx-1][my]));
				break;
	}
}

int goodRight(Cell maze[][16], int mx, int my, int dir)
{
	switch(dir){
		case WEST:
			return (openNorth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my+1]));
				break;
		case NORTH:
			return (openEast(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx+1][my]));
				break;
		case EAST:
			return (openSouth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my-1]));
				break;
		case SOUTH:
			return (openWest(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx-1][my]));
				break;
	}
}

int goodLeft(Cell maze[][16], int mx, int my, int dir)
{
	switch(dir){
		case EAST:
			return (openNorth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my+1]));
				break;
		case SOUTH:
			return (openEast(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx+1][my]));
				break;
		case WEST:
			return (openSouth(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx][my-1]));
				break;
		case NORTH:
			return (openWest(maze,mx,my)&&
				closer(&maze[mx][my],&maze[mx-1][my]));
				break;
	}
}

int closer(Cell *current, Cell *target)
{
	return (getDist(target)<getDist(current));
}

int inCenter(int mx, int my)
{
	return( (mx==7||mx==8)&&(my==7||my==8) );
}
int inStart(int mx, int my)
{
	return(mx==0 && my==0);
}

int seeFWall(int x, int y, int dir, Cell testMaze[][16])
{
	switch(dir){
		case NORTH:
			return (hasNorth(&testMaze[x][y])||!isValid(x,y+1));
			break;
		case EAST:
			return (hasEast(&testMaze[x][y])||!isValid(x+1,y));
			break;
		case SOUTH:
			return (hasNorth(&testMaze[x][y-1])||!isValid(x,y-1));
			break;
		case WEST:
			return (hasEast(&testMaze[x-1][y])||!isValid(x-1,y));
			break;
	}
}

int seeRWall(int x, int y, int dir, Cell testMaze[][16])
{
	switch(dir){
		case WEST:
			return (hasNorth(&testMaze[x][y])||!isValid(x,y+1));
			break;
		case NORTH:
			return (hasEast(&testMaze[x][y])||!isValid(x+1,y));
			break;
		case EAST:
			return (hasNorth(&testMaze[x][y-1])||!isValid(x,y-1));
			break;
		case SOUTH:
			return (hasEast(&testMaze[x-1][y])||!isValid(x-1,y));
			break;
	}
}

int seeLWall(int x, int y, int dir, Cell testMaze[][16])
{
	switch(dir){
		case EAST:
			return (hasNorth(&testMaze[x][y])||!isValid(x,y+1));
			break;
		case SOUTH:
			return (hasEast(&testMaze[x][y])||!isValid(x+1,y));
			break;
		case WEST:
			return (hasNorth(&testMaze[x][y-1])||!isValid(x,y-1));
			break;
		case NORTH:
			return (hasEast(&testMaze[x-1][y])||!isValid(x-1,y));
			break;
	}
}
