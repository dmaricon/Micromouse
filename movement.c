#include "movement.h"
#include "p33FJ128MC802.h"
#include "sensors.h"
#include "mouse.h"
#include "maze.h"
#include "cell.h"

#define MAXDUTY 2046
#define MINDUTY 0

//speed control gains
#define kP_SPEED 100
#define kD_SPEED
#define kI_SPEED

extern double rDispTotal, lDispTotal;
extern double rVelocity, lVelocity;
extern int fr, fl;
extern Cell maze[16][16];
extern int x,y,dir;
extern int returnRun;

double tsr0 = 0; //initial target speed right
double tsl0 = 0; //initial target speed left
double tsr = 0; //adjusted target speed right
double tsl = 0; //adjusted target speed left

double targetDist; //target distance for movement

int tracking = 0;
//int moving = 0;
int mapping = 1;
int turning = 0;

void rSpdCntrl()
{
    double rError;
    int rduty = RDUTY;
    
    //get errors
    if(rVelocity < 0)
        rError = tsr + rVelocity;
    else
        rError = tsr - rVelocity;
    
    rduty += (int)(rError*kP_SPEED);

    //duty cycle limits
    if(rduty < MINDUTY)
        rduty = MINDUTY;
    if(rduty > MAXDUTY)
        rduty = MAXDUTY;
    
    RDUTY = rduty;
}
void lSpdCntrl()
{
    double lError;
    int lduty = LDUTY;

    //get errors
    if(lVelocity < 0)
        lError = tsl + lVelocity;
    else
        lError = tsl - lVelocity;

    lduty += (int)(lError*kP_SPEED);

    //duty cycle limits
    if(lduty < MINDUTY)
        lduty = MINDUTY;
    if(lduty > MAXDUTY)
        lduty = MAXDUTY;

    LDUTY = lduty;
}
void spdCntrl()
{
    rSpdCntrl();
    lSpdCntrl();
}
void cellForward(int cells)
{
//    while(targetDist!=0);
//    targetDist = CELL*cells;
    rDispTotal = lDispTotal = 0;
//    moving = 1;
    forward();
    if(mapping){ //check walls halfway through cell
        while(DISPLACEMENT < CELL/2);
        mapWalls();
        update(maze,x,y,dir);
        if(returnRun)
            flood2start(maze);
        else
            flood2center(maze);
        while(DISPLACEMENT < CELL);
    }
}
void right90()
{
//    while(targetDist!=0); //wait till done moving
    turning = 1;
    rDispTotal = lDispTotal = 0;
    right();
    while(lDispTotal/2 - rDispTotal/2 < 6.5);
    brake();
    delayms(250);
    turning = 0;
}
void left90()
{
//    while(targetDist!=0);
    turning = 1;
    rDispTotal = lDispTotal = 0;
    left();
    while(rDispTotal/2 - lDispTotal/2 < 6.5);
    brake();
    delayms(250);
    turning = 0;
}
void aboutFace()
{
    while(targetDist!=0);
    turning = 1;
    rDispTotal = lDispTotal = 0;
    right();
    while(lDispTotal/2 - rDispTotal/2 < 14.5);
    brake();
    delayms(250);
    turning = 0;
}

void rForward()
{
    PORTBbits.RB4 = 1;
    PORTAbits.RA4 = 1;
}
void lForward()
{
    PORTBbits.RB15 = 0;
    PORTAbits.RA3 = 1;
}
void forward()
{
    tracking = 1;
    rForward();
    lForward();
}
void right()
{
    tracking = 0;
    rReverse();
    lForward();
}
void left()
{
    tracking = 0;
    rForward();
    lReverse();
}
void rReverse()
{
    PORTBbits.RB4 = 0;
    PORTAbits.RA4 = 1;
}
void lReverse()
{
    PORTBbits.RB15 = 1;
    PORTAbits.RA3 = 1;
}
void reverse()
{
    tracking = 1;
    rReverse();
    lReverse();
}
void rBrake()
{
    tracking = 0;
    PORTAbits.RA4 = 0;
}
void lBrake()
{
    PORTAbits.RA3 = 0;
}
void brake()
{
    rBrake();
    lBrake();
}
