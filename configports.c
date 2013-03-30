#include "p33FJ128MC802.h"
#include "interrupts.h"
#include "QEI.h"
#include "delay.h"
#include "libpic30.h"
#include "sensors.h"
#include "configports.h"

void config_ports()
{
    __builtin_write_OSCCONL(OSCCON & (~(1<<6))); // unlock IOLock

    CMCON=0;
    AD1PCFGL= 0b1111110000;

    //emitter ports
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB7 = 0;

    TRISAbits.TRISA1 = 1;       //Set Left side detector to input

    TRISBbits.TRISB12 = 0;
    PORTBbits.RB12 = 0;         //Set port to high so motors don't run

    TRISBbits.TRISB14 = 0;
    PORTBbits.RB14 = 0;         //Set port to high so motors don't run

    TRISBbits.TRISB5 = 1;       //Set QEI Channels to inputs
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;

    TRISBbits.TRISB4 = 0;       //Right Direction
    PORTBbits.RB4 = 1;

    TRISBbits.TRISB15 = 0;       //Left Direction
    PORTBbits.RB15 = 1;

    TRISAbits.TRISA4 = 0;      // Right Brake
    PORTAbits.RA4 = 1;

    TRISAbits.TRISA3 = 0;      // Left Brake
    PORTAbits.RA3 = 1;

    /* Right Motor QEI */
    RPINR14bits.QEA1R = 5;         // QEIA Input tied to RP5 (QEA1R<4:0> Pin 2)
    RPINR14bits.QEB1R = 6;         // QEIB Input tied to RP6 (QEB1R<4:0> Pin 3)
    /* Left Motor QEI */
    RPINR16bits.QEA2R = 2;
    RPINR16bits.QEB2R = 3;

     //Lock the registers
    __builtin_write_OSCCONL(OSCCON | (1<<6));


}