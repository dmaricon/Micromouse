#ifndef MOUSE_H
#define MOUSE_H

#include "maze.h"
#include "cell.h"
#include "queue.h"

void update(Cell maze[][16], int mx, int my, int dir);

void flood(Cell maze[][16], Queue *q, int n);

void floodLevel(int n, int d, Queue *q); /* Sets the front n distances to d */

void flood2center(Cell maze[][16]); /* Floods with the center as goal */

void flood2start(Cell maze[][16]); /* Floods with the start cell as goal */

void move(Cell maze[][16], int *mx, int *my, int *dir);

void turnRight(int *dir);

void turnLeft(int *dir);

void turnAround(int *dir);

void go(int *mx, int *my, int dir);

void goRight(int *mx, int *my, int *dir);

void goLeft(int *mx, int *my, int *dir);

void goBack(int *mx, int *my, int *dir);

int goodFront(Cell maze[][16], int mx, int my, int dir);

int goodRight(Cell maze[][16], int mx, int my, int dir);

int goodLeft(Cell maze[][16], int mx, int my, int dir);

int closer(Cell *current, Cell *target);

int inCenter(int mx, int my);

int inStart(int mx, int my);

#endif
