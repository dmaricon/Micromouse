#include "pwm.h"
#include "p33FJ128MC804.h"


/*This is part of the project*/
void initPWM(void)
{
    P1TCONbits.PTEN = 1;         // Disable PWM Time Base Timer (PTEN)
    P2TCONbits.PTEN = 1;
    P1TCONbits.PTOPS = 0;        // PWM timer 1:1 post-scale  (PTOPS <3:0>)
    P2TCONbits.PTOPS = 0;
    P1TCONbits.PTCKPS = 0;       // PWM timer 1:1 pre-scale   (PTCKPS <1:0>)
    P2TCONbits.PTCKPS = 0;
    P1TCONbits.PTMOD = 0;        // PWM operates in free-running Mode continuously (PTMOD <1:0>)
    P2TCONbits.PTMOD = 0;

    P1TMRbits.PTMR = 0;                  // PWM counter value, start at 0 (PTMR <14:0>)
    P2TMRbits.PTMR = 0;
    P1TPERbits.PTPER = 1022;               // PWM Timebase period, determines PWM frequency (PTPER <14:0>)
    P2TPERbits.PTPER = 1022;                            // PxDCY Value for 100% Duty Cycle PTPER*2 (2047)
                                // Gives 11 bits of PWM Resolution, See Table 14-1

    PWM1CON1bits.PMOD1 = 0b1;	//PWM i/o pair in independent mode
    PWM2CON1bits.PMOD1 = 0b1;

    PWM1CON1bits.PEN1H = 1;      // PWM1H1 pin is enabled for left motor
    PWM2CON1bits.PEN1H = 1;      // PWM2H1 pin is enabled for right motor

    PWM2CON2bits.IUE = 0b1;
    PWM1CON2bits.IUE = 0b1;		//Duty Cycle updates are immediate

    P1DC1 = 0;             //Duty Cycle PWM1H1
    P2DC1 = 0;             //Duty Cycle PWM1H2
}

