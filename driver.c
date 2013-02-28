/* File	:	maze.c			*
 * By	:	Daniel Mariconda	*
 * ID	:	dmaricon		*
 * Date	:	2/1/12			*/

/*	Test driver for maze generating/solving		*/

#include <stdio.h>
#include "maze.h"
#include "queue.h"
#include "cell.h"
#include "mouse.h"

main()
{
	int x,y,dir;
	Cell maze[16][16];
	Cell testMaze[16][16];

	x = 0;
	y = 0;
	dir = NORTH;

	m_init(maze);
	m_init(testMaze);
	generateBinary(testMaze);
	printf("Generated Maze\n");
	display(testMaze,x,y);
	while(getchar()!='\n');

	display(maze,x,y);

	while(1){
		while(!inCenter(x,y)){
			while(getchar()!='\n');
			update(maze,x,y,dir,testMaze);
			flood2center(maze);
			display(maze,x,y);
			showDirection(dir);
			move(maze,&x,&y,&dir);
		}
		while(!inStart(x,y)){
			while(getchar()!='\n');
			update(maze,x,y,dir,testMaze);
			flood2start(maze);
			display(maze,x,y);
			showDirection(dir);
			move(maze,&x,&y,&dir);
		}
	}
}
