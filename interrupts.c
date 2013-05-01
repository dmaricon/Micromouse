#include "p33FJ128MC804.h"
#include "interrupts.h"
#include "movement.h"
#include "sensors.h"
#include "QEI.h"
#include "led.h"


extern int tracking,moving,turning;
extern double rDispTotal,lDispTotal,targetDist,lVelocity,rVelocity;
extern double tsr0,tsl0,tsr,tsl,targetSpeed;
extern int accel,accel2,decel;
extern int rAction,lAction;

int button = 0;
#define BUTTON PORTAbits.RA0
int fl,sl,fr,sr;
double accelInterval = CELL / 4;

void __attribute__((__interrupt__,__shadow__,no_auto_psv)) _T2Interrupt(void) {
   IFS0bits.T2IF = 0;

   rPosCalc();
   lPosCalc();
   rVelocityCalc();
   lVelocityCalc();

   tsr0 = tsl0 = tsr = tsl = CELL * 1.5;
   if (accel) {
      if (DISPLACEMENT < accelInterval)
         tsr0 = tsl0 = BASE_SPEED + (DISPLACEMENT / accelInterval)*(targetSpeed - BASE_SPEED);
      else
         tsr0 = tsl0 = targetSpeed;
   }
   else if(accel2){
      if (DISPLACEMENT < accelInterval)
         tsr0 = tsl0 = TURN_SPEED + (DISPLACEMENT / accelInterval)*(targetSpeed - TURN_SPEED);
      else
         tsr0 = tsl0 = targetSpeed;
   }
   if(decel && DISPLACEMENT > targetDist - accelInterval)
      tsr0 = tsl0 = TURN_SPEED + ((targetDist - DISPLACEMENT) / accelInterval)*(targetSpeed - TURN_SPEED);

   if (!turning)
      track();

   spdCntrl();

   if (rAction == 1 && lAction == 1 && !turning) {
      fl = sensorRead(FLD);
      fr = sensorRead(FRD);
      if (FRONTSTOP)
         rDispTotal = lDispTotal = targetDist;
   }
   //    if(FRONTWALL)
   //        ledBlue();
   //    else
   //        ledGreen();
}

void __attribute__((__interrupt__,__shadow__,no_auto_psv)) _T1Interrupt(void) {
   IFS0bits.T1IF = 0;
}

//void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
//{
//    button = 1;
//    IFS1bits.INT1IF = 0;
//}

void init_Button() {
   TRISAbits.TRISA0 = 1;
   //    RPINR0bits.INT1R = 38;  //Set to interrupt
   //
   //    IPC5bits.INT1IP = 7;
   //    INTCON2bits.INT1EP = 1; //interrupt on falling edge
   //    IFS1bits.INT1IF = 0;    //clear flag
   //    IEC1bits.INT1IE =1;     // enable
}

void buttonStart() {
   ledRed();
   while (!button)
      button = !BUTTON;
   button = 0;
   ledYellow();
   sensorStart();
}

void enable_T1(void) {
   T1CONbits.TON = 0;// Disable Timer1 Module
   T1CONbits.TCS = 0;// Select internal clock cycle
   T1CONbits.TGATE = 0;// Disable Gated timer mode
   T1CONbits.TCKPS = 0b10;// Prescaler 64

   TMR1 = 0x00;// Clears Timer1 register
   PR1 = 1875;// interrupt period 3 ms

   IPC0bits.T1IP = 6;// Sets priority
   IFS0bits.T1IF = 0;// Clear Timer1 Interrupt Flag
   IEC0bits.T1IE = 0;// Enable Timer1 Interrupt*/
   T1CONbits.TON = 1;// Starts Timer1
}

void enable_T2(void) {
   T2CONbits.TON = 0;// Disable Timer1 Module
   T2CONbits.TCS = 0;// Select internal clock cycle
   T2CONbits.TGATE = 0;// Disable Gated timer mode
   T2CONbits.TCKPS = 0b10;// Prescaler 64

   TMR2 = 0x00;// Clears Timer2 register
   PR2 = 625;// PR2 = interrupt period(s) * 40,000,000 / 64

   IPC1bits.T2IP = 6;// Sets priority
   IFS0bits.T2IF = 0;// Clear Interrupt Flag
   IEC0bits.T2IE = 1;// Enable Interrupt
   T2CONbits.TON = 1;// Starts Timer
}
