/* 
 * File:   sensors.h
 * Author: graigg
 *
 * Created on January 7, 2013, 3:58 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H


//emitter macros
#define FRE LATBbits.LATB7
#define SRE LATBbits.LATB8
#define SLE LATBbits.LATB9
#define FLE LATBbits.LATB13

//detectors
#define FLD 0
#define SLD 1
#define FRD 2
#define SRD 3

//ideal values
#define RIDEAL 230
#define LIDEAL 280
#define FLIDEAL 540
#define FRIDEAL 600
#define FLMIN 200       //UPDATE THESE FOR MID-CELL MAPPING
#define FRMIN 230

#define RIGHTWALL (sr > 160)
#define LEFTWALL (sl > 190)
#define FRONTWALL ((fl > FLMIN)||(fr > FRMIN))
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

