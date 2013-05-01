#include "p33FJ128MC804.h"
#include "interrupts.h"
#include "QEI.h"
#include "delay.h"
#include "libpic30.h"
#include "sensors.h"
#include "configports.h"

void config_ports()
{
    AD1PCFGL= 0b100001111;

    //emitter ports
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA9 = 0;
    TRISBbits.TRISB4 = 0;
    TRISAbits.TRISA8 = 0;

    TRISCbits.TRISC6 = 0;
    LATCbits.LATC6 = 1;         //Set port to high so motors don't run

    TRISBbits.TRISB14 = 0;
    LATBbits.LATB14 = 1;        //Set port to high so motors don't run

    TRISCbits.TRISC4 = 1;       //Set QEI Channels to inputs
    TRISCbits.TRISC3 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB5 = 1;

    TRISAbits.TRISA7 = 0;       //Right Direction
    LATAbits.LATA7 = 0;

    TRISCbits.TRISC8 = 0;       //Left Direction
    LATCbits.LATC8 = 0;

    TRISAbits.TRISA10 = 0;      // Right Brake
    LATAbits.LATA10 = 0;

    TRISCbits.TRISC9 = 0;      // Left Brake
    LATCbits.LATC9 = 0;

    /* Right Motor QEI */
    RPINR14bits.QEA1R = 20;  // QEIA Input tied to RP20
    RPINR14bits.QEB1R = 19;  // QEIB Input tied to RP19
    /* Left Motor QEI */
    RPINR16bits.QEA2R = 5;
    RPINR16bits.QEB2R = 6;

    /* LED ports */
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB7 = 0;
}