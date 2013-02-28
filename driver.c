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

	#ifdef TEST
	Cell testMaze[16][16];
	#endif

	x = 0;
	y = 0;
	dir = NORTH;

	m_init(maze);

	#ifdef TEST
	m_init(testMaze);
	generateBinary(testMaze);
	printf("Generated Maze\n");
	display(testMaze,x,y);
	while(getchar()!='\n');
	display(maze,x,y);
	#endif

	while(1){
		while(!inCenter(x,y)){
			#ifdef TEST
			while(getchar()!='\n');
			update(maze,x,y,dir,testMaze);
			#endif

			flood2center(maze);

			#ifdef TEST
			display(maze,x,y);
			showDirection(dir);
			#endif

			move(maze,&x,&y,&dir);
		}
		while(!inStart(x,y)){

			#ifdef TEST
			while(getchar()!='\n');
			update(maze,x,y,dir,testMaze);
			#endif

			flood2start(maze);

			#ifdef TEST
			display(maze,x,y);
			showDirection(dir);
			#endif

			move(maze,&x,&y,&dir);
		}
	}
}
