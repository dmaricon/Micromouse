#include "mouse.h"
#include "movement.h"
#include "sensors.h"

extern int frontWall,rightWall,leftWall;
extern int fr,fl,sr,sl;
extern int gx,gy,gd;
extern int sturning;

#define INVALID -1

typedef enum {
   FORWARD,RIGHT,LEFT
} Move;
Move moves[256];
int ind = 0;
int savingPath = 0;

//#define MINIMAZE

void update(Cell maze[][16],int mx,int my,int dir) {
   if (frontWall) addFWall(maze,mx,my,dir);
   if (rightWall) addRWall(maze,mx,my,dir);
   if (leftWall) addLWall(maze,mx,my,dir);
   visit(&maze[mx][my]);
}

void flood(Cell maze[][16],Queue *q,int n) {
   int d = 0;
   int x = 0;
   int y = 0;
   int n1 = n;
   int n2 = 0;

   while (!empty(q)) {
      floodLevel(n1,d,q);
      d++;
      n2 = n1;
      n1 = 0;
      for (;n2 > 0;n2--) { /* Check neighbors of each cell in queue */

         x = getx(qfront(q));
         y = gety(qfront(q));

         if (!(savingPath && !visited(&maze[x][y + 1])) &&
                 openNorth(maze,x,y) && getDist(&maze[x][y + 1]) == 255 &&
                 !checked(&maze[x][y + 1])) {
            in(q,&maze[x][y + 1]);
            n1++;
         }
         if (!(savingPath && !visited(&maze[x + 1][y])) &&
                 openEast(maze,x,y) && getDist(&maze[x + 1][y]) == 255 &&
                 !checked(&maze[x + 1][y])) {
            in(q,&maze[x + 1][y]);
            n1++;
         }
         if (!(savingPath && !visited(&maze[x][y - 1])) &&
                 openSouth(maze,x,y) && getDist(&maze[x][y - 1]) == 255 &&
                 !checked(&maze[x][y - 1])) {
            in(q,&maze[x][y - 1]);
            n1++;
         }
         if (!(savingPath && !visited(&maze[x - 1][y])) &&
                 openWest(maze,x,y) && getDist(&maze[x - 1][y]) == 255 &&
                 !checked(&maze[x - 1][y])) {
            in(q,&maze[x - 1][y]);
            n1++;
         }
         out(q);
      }
   }

}

void floodLevel(int n,int d,Queue *q) {
   int i;
   for (i = 0;i < n;i++) {
      setDist(q->contents[(getFront(q) + i) % QSIZE],d);
   }
}

void flood2center(Cell maze[][16]) {
   Queue q;
   int x = 0;
   int y = 0;
   q_init(&q);

   for (x = 0;x < 16;x++)
      for (y = 0;y < 16;y++)
         clearDist(&maze[x][y]);

#ifndef MINIMAZE
   in(&q,&maze[7][8]);
   in(&q,&maze[8][8]);
   in(&q,&maze[7][7]);
   in(&q,&maze[8][7]);

   flood(maze,&q,4);
#else
   in(&q,&maze[3][3]);
   flood(maze,&q,1);
#endif
}

void flood2start(Cell maze[][16]) {
   Queue q;
   int x = 0;
   int y = 0;
   q_init(&q);

   for (x = 0;x < 16;x++)
      for (y = 0;y < 16;y++)
         clearDist(&maze[x][y]);

   in(&q,&maze[0][0]);

   flood(maze,&q,1);
}

void move(Cell maze[][16],int *mx,int *my,int *dir) {
   if (goodFront(maze,*mx,*my,*dir)) go(mx,my,*dir);
   else if (goodRight(maze,*mx,*my,*dir)) goRight(mx,my,dir);
   else if (goodLeft(maze,*mx,*my,*dir)) goLeft(mx,my,dir);
   else goBack(mx,my,dir);
}

void turnRight(int *dir) {
   virtualRight(dir);
   if (!savingPath)
      right90();
}

void turnLeft(int *dir) {
   virtualLeft(dir);
   if (!savingPath) {
      left90();
   }
}

void virtualRight(int *dir) {
   *dir = (*dir + 1) % 4;
}

void virtualLeft(int *dir) {
   *dir = (*dir + 3) % 4;
}

void turnAround(int *dir) {
   *dir = (*dir + 2) % 4;
   aboutFace();
}

void go(int *mx,int *my,int dir) {
   virtualForward(mx,my,dir);
   if (!savingPath)
      cellForward(1);
   else
      moves[ind] = FORWARD;
}

void virtualForward(int* mx,int* my,int dir) {
   switch (dir) {
      case NORTH:
         *my = *my + 1;
         break;
      case EAST:
         *mx = *mx + 1;
         break;
      case SOUTH:
         *my = *my - 1;
         break;
      case WEST:
         *mx = *mx - 1;
         break;
   }
}

void goRight(int *mx,int *my,int *dir) {
   turnRight(dir);
   go(mx,my,*dir);
   if (savingPath)
      moves[ind] = RIGHT;
}

void goLeft(int *mx,int *my,int *dir) {
   turnLeft(dir);
   go(mx,my,*dir);
   if (savingPath)
      moves[ind] = LEFT;
}

void goBack(int *mx,int *my,int *dir) {
   turnAround(dir);
   go(mx,my,*dir);
}

int goodFront(Cell maze[][16],int mx,int my,int dir) {
   switch (dir) {
      case NORTH:
         return (openNorth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my + 1]));
         break;
      case EAST:
         return (openEast(maze,mx,my) && closer(&maze[mx][my],&maze[mx + 1][my]));
         break;
      case SOUTH:
         return (openSouth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my - 1]));
         break;
      case WEST:
         return (openWest(maze,mx,my) && closer(&maze[mx][my],&maze[mx - 1][my]));
         break;
      default:
         return 0;
   }
}

int goodRight(Cell maze[][16],int mx,int my,int dir) {
   switch (dir) {
      case WEST:
         return (openNorth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my + 1]));
         break;
      case NORTH:
         return (openEast(maze,mx,my) && closer(&maze[mx][my],&maze[mx + 1][my]));
         break;
      case EAST:
         return (openSouth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my - 1]));
         break;
      case SOUTH:
         return (openWest(maze,mx,my) && closer(&maze[mx][my],&maze[mx - 1][my]));
         break;
      default:
         return 0;
   }
}

int goodLeft(Cell maze[][16],int mx,int my,int dir) {
   switch (dir) {
      case EAST:
         return (openNorth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my + 1]));
         break;
      case SOUTH:
         return (openEast(maze,mx,my) && closer(&maze[mx][my],&maze[mx + 1][my]));
         break;
      case WEST:
         return (openSouth(maze,mx,my) && closer(&maze[mx][my],&maze[mx][my - 1]));
         break;
      case NORTH:
         return (openWest(maze,mx,my) && closer(&maze[mx][my],&maze[mx - 1][my]));
         break;
      default:
         return 0;
   }
}

int closer(Cell *current,Cell *target) {
   return (getDist(target) < getDist(current));
}

int inCenter(int mx,int my) {
#ifndef MINIMAZE
   return ((mx == 7 || mx == 8) && (my == 7 || my == 8));
#else
   return (mx == 3 && my == 3);
#endif
}

int inStart(int mx,int my) {
   return (mx == 0 && my == 0);
}

void savePath(Cell maze[][16]) {
   int x,y,dir;
   int i;

   for (i = 0;i < 256;i++)
      moves[i] = INVALID;

   x = y = 0;
   dir = NORTH;
   savingPath = 1;
   flood2center(maze);

   for (ind = 0;!inCenter(x,y);ind++) {
      move(maze,&x,&y,&dir);
   }
   savingPath = 0;
}

void executePath() {
   int i,j;
   double n;

   for (i = 0;moves[i] != INVALID;i++) {
      switch (moves[i]) {
         case FORWARD:
            n = 1;
            if (i > 0 && moves[i - 1] != FORWARD){// coming out of turn
               if (sturning)
                  n += 0.5;
               else
                  n += 1;
            }
            for (j = i + 1;moves[j] == FORWARD;i++,j++,n++);
            if (moves[i + 1] != INVALID && sturning)// approaching turn
               n -= 0.5;
            cellForward(n);
            break;
         case RIGHT:
            if (sturning) {
               sRight();
            }
            else {
               if (moves[i - 1] != FORWARD) {
                  cellForward(1);
               }
               right90();
            }
            break;
         case LEFT:
            if (sturning) {
               sLeft();
            }
            else {
               if (moves[i - 1] != FORWARD) {
                  cellForward(1);
               }
               left90();
            }
            break;
         default:
            break;
      }
   }
   if (sturning && moves[i-1]!=FORWARD)
      cellForward(0.5);
}

void closeCenter(Cell maze[][16],int x,int y,int dir) {
   switch (dir) {
      case NORTH:
         addLWall(maze,7,7,dir);
         addLWall(maze,7,8,dir);
         addFWall(maze,7,8,dir);
         addFWall(maze,8,8,dir);
         addRWall(maze,8,8,dir);
         addRWall(maze,8,7,dir);
         if (x == 7)
            addFWall(maze,8,6,dir);
         else
            addFWall(maze,7,6,dir);
         break;
      case EAST:
         addLWall(maze,7,8,dir);
         addLWall(maze,8,8,dir);
         addFWall(maze,8,8,dir);
         addFWall(maze,8,7,dir);
         addRWall(maze,8,7,dir);
         addRWall(maze,7,7,dir);
         if (y == 7)
            addFWall(maze,6,8,dir);
         else
            addFWall(maze,6,7,dir);
         break;
      case SOUTH:
         addLWall(maze,8,8,dir);
         addLWall(maze,8,7,dir);
         addFWall(maze,8,7,dir);
         addFWall(maze,7,7,dir);
         addRWall(maze,7,7,dir);
         addRWall(maze,7,8,dir);
         if (x == 7)
            addFWall(maze,8,9,dir);
         else
            addFWall(maze,7,9,dir);
         break;
      case WEST:
         addLWall(maze,8,7,dir);
         addLWall(maze,7,7,dir);
         addFWall(maze,7,7,dir);
         addFWall(maze,7,8,dir);
         addRWall(maze,7,8,dir);
         addRWall(maze,8,8,dir);
         if (y == 7)
            addFWall(maze,9,8,dir);
         else
            addFWall(maze,9,7,dir);
         break;
   }
}