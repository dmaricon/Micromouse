/* 
 * File:   sensors.h
 * Author: graigg
 *
 * Created on January 7, 2013, 3:58 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H


//emitter macros
#define FRE LATAbits.LATA8 //LATBbits.LATB7
#define SRE LATBbits.LATB4 //LATBbits.LATB8
#define SLE LATAbits.LATA9 //LATBbits.LATB9
#define FLE LATAbits.LATA4 //LATBbits.LATB13

//detectors
#define FLD 6
#define SLD 7
#define FRD 4
#define SRD 5

//ideal values
#define RIDEAL 290
#define LIDEAL 240
#define FLIDEAL 500
#define FRIDEAL 500
#define FMIN 50
#define FLMIN 50
#define FRMIN 50

#define RIGHTWALL (sr > 100)
#define LEFTWALL (sl > 70)

#define RIGHTWALL_T (sr > RIDEAL)
#define LEFTWALL_T (sl > LIDEAL)

#define FRONTWALL ((fl+fr)/2 > FMIN)
#define FRONTSTOP ((fl > FLIDEAL)||(fr > FRIDEAL))

void initADC();
void track();
void mapWalls();
void FR_Noise_Read();
int sensorRead(int sensor);
void emitterOn(int sensor);
void emitterOff(int sensor);
void choose_sensor(int sensor);
void sensorStart();
void delayms(int ms);
#define FCY 40000000UL          // 40 MIPS
#define Fosc 80000000           // Fosc = 2*FCY (80 MHz)
#define MIPS 40                 // MIPS = Fcy/1000000
#define TCY  1/FCY              // TCY = 1/Fcy
                                // TCY = 4*Tosc

#endif	/* SENSORS_H */

