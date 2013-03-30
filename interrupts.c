#include "p33FJ128MC802.h"
#include "interrupts.h"
#include "movement.h"
#include "sensors.h"
#include "QEI.h"


extern int tracking, moving, turning;
extern double rDispTotal, lDispTotal, targetDist;

int fl,sl,fr,sr;

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;

    rPosCalc();
    lPosCalc();
    rVelocityCalc();
    lVelocityCalc();

    fl = sensorRead(FLD);
    sl = sensorRead(SLD);
    fr = sensorRead(FRD);
    sr = sensorRead(SRD);

    if(tracking)
        track();

    spdCntrl();
    
    //check for completed movement
//    if((!turning) && (DISPLACEMENT > targetDist||DISPLACEMENT < (-targetDist)||FRONTSTOP)){
//        brake();
////        moving = 0;
//        rDispTotal = 0;
//        lDispTotal = 0;
//        targetDist = 0;
//    }
}

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
}

void enable_T1(void)
{
    T1CONbits.TON = 0;      // Disable Timer1 Module
    T1CONbits.TCS = 0;      // Select internal clock cycle
    T1CONbits.TGATE=0;      // Disable Gated timer mode
    T1CONbits.TCKPS=0b10;   // Prescaler 64

    TMR1=0x00;              // Clears Timer1 register
    PR1=1875;               // interrupt period 3 ms

    IPC0bits.T1IP=7;        // Sets priority
    IFS0bits.T1IF=0;        // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE=0;        // Enable Timer1 Interrupt*/
    T1CONbits.TON=1;        // Starts Timer1
//    for(i=0;i<256;i++)
//        read_velocity1[i]=0;
//    i=0;

}

void enable_T2(void)
{
    T2CONbits.TON = 0;      // Disable Timer1 Module
    T2CONbits.TCS = 0;      // Select internal clock cycle
    T2CONbits.TGATE=0;      // Disable Gated timer mode
    T2CONbits.TCKPS=0b10;   // Prescaler 64

    TMR2=0x00;              // Clears Timer2 register
    PR2=625;               // PR2 = interrupt period(s) * 40,000,000 / 64

    IPC1bits.T2IP=7;        // Sets priority
    IFS0bits.T2IF=0;        // Clear Interrupt Flag
    IEC0bits.T2IE=1;        // Enable Interrupt
    T2CONbits.TON=1;        // Starts Timer
//    for(i=0;i<256;i++)
//        read_velocity2[i]=0;
//    i=0;
}
