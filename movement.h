/* 
 * File:   movement.h
 * Author: graigg
 *
 * Created on March 1, 2013, 5:42 PM
 */

#ifndef MOVEMENT_H
#define	MOVEMENT_H

#define RDUTY P1DC2
#define LDUTY P1DC1

#define DISPLACEMENT (rDispTotal/2 + lDispTotal/2)

#define CELL 18

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
void cellForward(int cells);

#endif	/* MOVEMENT_H */

