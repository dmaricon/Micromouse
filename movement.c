#include "movement.h"
#include "p33FJ128MC804.h"
#include "sensors.h"
#include "mouse.h"
#include "maze.h"
#include "cell.h"

#define MAXDUTY 2046
#define MINDUTY 0

//speed control gains
#define kP_SPEED 100
#define kD_SPEED 100
#define kI_SPEED

#define TURN 5.0
#define AROUND 10.5
#define SDIST 14.0 //outer wheel distance for s-turn

extern double rDispTotal,lDispTotal;
extern double rVelocity,lVelocity;
extern int fr,fl;
extern Cell maze[16][16];
extern int x,y,dir;
extern int returnRun;
extern int sright,sleft;
extern int sturning;
extern double accelInterval,accelInterval0;
extern double targetSpeed,targetSpeed0;

double tsr0 = 0;//initial target speed right
double tsl0 = 0;//initial target speed left
double tsr = 0;//adjusted target speed right
double tsl = 0;//adjusted target speed left
double rError = 0;
double lError = 0;
double rErrorPrev = 0;
double lErrorPrev = 0;

#define BRAKE 0
#define FORWARD 1
#define REVERSE 2
int lAction = BRAKE;
int rAction = BRAKE;

#define RERROR_DIFF (rError-rErrorPrev)
#define LERROR_DIFF (lError-lErrorPrev)

double targetDist;//target distance for movement

int tracking = 0;
int mapping = 0;
int turning = 0;
int sright = 0;
int sleft = 0;
int accel = 0;
int accel2 = 0;
int decel = 0;

void rSpdCntrl() {
   double ts = tsr;
   int rduty = RDUTY;

   if (sright)
      ts = (double)CELL;
   else if (sleft)
      ts = (double)CELL * 3.0;

   //get errors
   rErrorPrev = rError;
   if (rVelocity < 0)
      rError = ts + rVelocity;
   else
      rError = ts - rVelocity;

   rduty += (int)(kP_SPEED * rError + kD_SPEED * RERROR_DIFF);

   //duty cycle limits
   if (rduty < MINDUTY)
      rduty = MINDUTY;
   else if (rduty > MAXDUTY)
      rduty = MAXDUTY;

   if (rduty == MINDUTY)
      rBrake();
   else switch (rAction) {
         case FORWARD:
            rForward();
            break;
         case REVERSE:
            rReverse();
            break;
         default:
            rBrake();
            break;
      }

   RDUTY = rduty;
}

void lSpdCntrl() {
   double ts = tsl;
   int lduty = LDUTY;

   if (sright)
      ts = (double)CELL * 3.0;
   else if (sleft)
      ts = (double)CELL;

   //get errors
   lErrorPrev = lError;
   if (lVelocity < 0)
      lError = ts + lVelocity;
   else
      lError = ts - lVelocity;

   lduty += (int)(kP_SPEED * lError + kD_SPEED * LERROR_DIFF);

   //duty cycle limits
   if (lduty < MINDUTY)
      lduty = MINDUTY;
   else if (lduty > MAXDUTY)
      lduty = MAXDUTY;

   if (lduty == MINDUTY)
      lBrake();
   else switch (lAction) {
         case FORWARD:
            lForward();
            break;
         case REVERSE:
            lReverse();
            break;
         default:
            lBrake();
            break;
      }

   LDUTY = lduty;
}

void spdCntrl() {
   rSpdCntrl();
   lSpdCntrl();
}

void cellForward(double cells) {
   rDispTotal = lDispTotal = 0;
   decel = 1;
   if(targetSpeed0 > 50 && cells < 2){
      targetSpeed = 50;
      accelInterval = CELL/2;
   }
   else{
      targetSpeed = targetSpeed0;
      accelInterval = accelInterval0;
   }
   accel = ((rVelocity/2 + lVelocity/2) < BASE_SPEED && !(CELL*cells < accelInterval * 2));
   accel2 = (sturning && !(CELL*cells < accelInterval * 2));

   targetDist = CELL*cells;
   forward();
   while (DISPLACEMENT < CELL / 2);

   if (mapping || returnRun){
      mapWalls();
      update(maze,x,y,dir);
   }
   if (returnRun)
      flood2start(maze);
   else
      flood2center(maze);

   while (DISPLACEMENT < targetDist);
   accel = decel = 0;
   targetSpeed = targetSpeed0;
   accelInterval = accelInterval0;
}

void sRight() {
   //   if (sturning) {
   accel = 0;
   rDispTotal = lDispTotal = 0;
   rForward();
   lForward();

   while (DISPLACEMENT < CELL * .15);
   rDispTotal = lDispTotal = 0;

   turning = sright = 1;
   while (lDispTotal < SDIST);
   turning = sright = 0;

   rDispTotal = lDispTotal = 0;
   while (DISPLACEMENT < CELL * .15);
   return;
   //   }
   //   cellForward(0.5);
   //   right90();
   //   cellForward(0.5);
}

void sLeft() {
   //   if (sturning) {
   accel = 0;
   rDispTotal = lDispTotal = 0;
   rForward();
   lForward();

   while (DISPLACEMENT < CELL * .15);
   rDispTotal = lDispTotal = 0;

   turning = sleft = 1;
   while (rDispTotal < SDIST);
   turning = sleft = 0;

   rDispTotal = lDispTotal = 0;
   while (DISPLACEMENT < CELL * .15);
   return;
   //   }
   //   cellForward(0.5);
   //   left90();
   //   cellForward(0.5);
}

void right90() {
   accel = 0;
   turning = 1;
   rDispTotal = lDispTotal = 0;
   right();
   while (lDispTotal / 2 - rDispTotal / 2 < TURN);
   brake();
   delayms(100);
   turning = 0;
}

void left90() {
   accel = 0;
   turning = 1;
   rDispTotal = lDispTotal = 0;
   left();
   while (rDispTotal / 2 - lDispTotal / 2 < TURN);
   //       right();
   //       while(lDispTotal/2 - rDispTotal/2 < TURN*3.36);
   brake();
   delayms(100);
   turning = 0;
}

void aboutFace() {
   accel = 0;
   turning = 1;
   rDispTotal = lDispTotal = 0;
   right();
   while (lDispTotal / 2 - rDispTotal / 2 < AROUND);
   brake();
   delayms(100);
   turning = 0;
}

void rForward() {
   rAction = FORWARD;
   LATAbits.LATA7 = 0;
   LATAbits.LATA10 = 1;
}

void lForward() {
   lAction = FORWARD;
   LATCbits.LATC8 = 1;
   LATCbits.LATC9 = 1;
}

void forward() {
   rForward();
   lForward();
}

void right() {
   rReverse();
   lForward();
}

void left() {
   rForward();
   lReverse();
}

void rReverse() {
   rAction = REVERSE;
   LATAbits.LATA7 = 1;
   LATAbits.LATA10 = 1;
}

void lReverse() {
   lAction = REVERSE;
   LATCbits.LATC8 = 0;
   LATCbits.LATC9 = 1;
}

void reverse() {
   rReverse();
   lReverse();
}

void rBrake() {
   LATAbits.LATA10 = 0;
}

void lBrake() {
   LATCbits.LATC9 = 0;
}

void brake() {
   rAction = lAction = BRAKE;
   rBrake();
   lBrake();
}
