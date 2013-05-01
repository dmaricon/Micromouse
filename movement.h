/* 
 * File:   movement.h
 * Author: graigg
 *
 * Created on March 1, 2013, 5:42 PM
 */

#ifndef MOVEMENT_H
#define	MOVEMENT_H

#define RDUTY P1DC1
#define LDUTY P2DC1

#define DISPLACEMENT (rDispTotal/2 + lDispTotal/2)
#define BASE_SPEED (5)
#define TURN_SPEED (CELL*1.5)

#define CELL 18.0

void rForward();
void rReverse();
void lForward();
void lReverse();
void forward();
void reverse();
void right();
void left();
void rBrake();
void lBrake();
void brake();
void rSpdCntrl();
void lSpdCntrl();
void spdCntrl();
void right90();
void left90();
void aboutFace();
void cellForward(double cells);
void sRight();
void sLeft();

#endif	/* MOVEMENT_H */

