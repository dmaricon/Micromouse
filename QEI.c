#include "QEI.h"
#include "p33FJ128MC804.h"

#define QEI_TO_DEGREE (360.0/16760) //value from testing
#define DEGREE_TO_CM .0050637513 // = Displacement(cm) / AngDisplacement

#define QEI_FREQ 1000 //timer2 interrupt freq (Hz)

#define ERROR_ADJUSTMENT (101.5/100.0) //observed error adjustment

#define MAX_CNT_PER_REV (512*2-1)
#define MAXSPEED (double)(((unsigned long)MAX_CNT_PER_REV*2048/125)*QEI_TO_DEGREE)
#define HALFMAXSPEED (double)(MAXSPEED/2)

double rVelocity = 0;
double lVelocity = 0;
double read_velocity1[256];
double read_velocity2[256];
double rAngPos[2] = {0,0};
double lAngPos[2] = {0,0};
double rDispTotal = 0;
double lDispTotal = 0;
int POS1CNTcopy = 0;
int POS2CNTcopy = 0;

void rPosCalc(void)
{
    POS1CNTcopy = (int)POS1CNT;
    if (POS1CNTcopy < 0)
        POS1CNTcopy = -POS1CNTcopy;
    rAngPos[1] = rAngPos[0];
    rAngPos[0] = (unsigned int)(((unsigned long)POS1CNTcopy*2048)/125);
    rAngPos[0] = rAngPos[0] * QEI_TO_DEGREE;
}
void lPosCalc(void)
{
    POS2CNTcopy = (int)POS2CNT;
    if (POS2CNTcopy < 0)
        POS2CNTcopy = -POS2CNTcopy;
    lAngPos[1] = lAngPos[0];
    lAngPos[0] = (unsigned int)(((unsigned long)POS2CNTcopy*2048)/125);
    lAngPos[0] = lAngPos[0] * QEI_TO_DEGREE;
}

void rVelocityCalc()
{
    rVelocity = rAngPos[1] - rAngPos[0];
    if(rVelocity >= 0)
    {
        if(rVelocity >= HALFMAXSPEED)
            rVelocity = rVelocity - MAXSPEED;
    }
    else
    {
        if(rVelocity < - HALFMAXSPEED)
            rVelocity = rVelocity + MAXSPEED;
    }

    //convert to cm, cm/s
    rVelocity *= DEGREE_TO_CM * ERROR_ADJUSTMENT;
    rDispTotal += rVelocity;
    rVelocity *= QEI_FREQ;
}
void lVelocityCalc()
{
    lVelocity = lAngPos[0] - lAngPos[1];
    if(lVelocity >= 0)
    {
        if(lVelocity >= HALFMAXSPEED)
            lVelocity = lVelocity - MAXSPEED;
    }
    else
    {
        if(lVelocity < - HALFMAXSPEED)
            lVelocity = lVelocity + MAXSPEED;
    }

    //convert to cm, cm/s
    lVelocity *= DEGREE_TO_CM * ERROR_ADJUSTMENT;
    lDispTotal += lVelocity;
    lVelocity *= QEI_FREQ;
}

void init_QEI(void)
{
    
    QEI1CONbits.QEISIDL = 0;        // Continue module operation in idle mode
    QEI2CONbits.QEISIDL = 0;

    QEI1CONbits.CNTERR = 0;         // Clear any count errors
    QEI2CONbits.CNTERR = 0;

    QEI1CONbits.UPDN = 1;           // Position Counter Direction is positive (+)
    QEI2CONbits.UPDN = 1;

    QEI1CONbits.SWPAB = 0;           // QEA and QEB not swapped, A leads B
    QEI2CONbits.SWPAB = 0;

    QEI1CONbits.INDX = 1;           // Read only - Index pin state status pin.
    QEI2CONbits.INDX = 1;

    QEI1CONbits.POSRES = 0;         // No index pulse reset
    QEI2CONbits.POSRES = 0;

    QEI1CONbits.QEIM = 0b101;       // Use 2x Update mode with reset on MAXxCNT match (QEIM <2:0>)
    QEI2CONbits.QEIM = 0b101;

    QEI1CONbits.PCDOUT = 0;        // Counter Direction of Status Output (Normal I/O pin operation)
    QEI2CONbits.PCDOUT = 0;

    DFLT1CONbits.CEID = 1;          // Interrupts for count errors are disabled
    DFLT2CONbits.CEID = 1;

    DFLT1CONbits.QEOUT = 0;         // Digital Output filter disabled
    DFLT2CONbits.QEOUT = 0;

    DFLT1CONbits.QECK = 0;          // 1:1 Digital Filter Clock Divide (QECK <2:0>)
    DFLT2CONbits.QECK = 0;

    POS1CNT = 0;                    // Initialize Position Counter => 0
    POS2CNT = 0;

    MAX1CNT = 2*512-1;
    MAX2CNT = 2*512-1;
}



