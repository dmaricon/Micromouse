#include "sensors.h"
#include "p33FJ128MC802.h"
#include "libpic30.h"
#include "delay.h"
#include "clock.h"
#define KERROR 5

//#define KTRACKING

int noise;
extern double tsr, tsl, tsr0, tsl0;
extern int fl,sl,fr,sr;
int rightWall = 0;
int leftWall = 0;
int frontWall = 0;

//tracking gains
#define kP_TRACKING 0.002
#define kD_TRACKING
#define kI_TRACKING

void track()
{
    int srError,slError;

    if(RIGHTWALL)
    {
#ifndef KTRACKING
        srError = RIDEAL - sr;
        tsr = tsr0*(1.0-kP_TRACKING*(double)srError);
        tsl = tsl0*(1.0+kP_TRACKING*(double)srError);
#else
        if(sr < RIDEAL - KERROR) //left of center
            tsr = tsr0 - tsr0 * 0.1;
        else if(sr > RIDEAL + KERROR) //right of center
            tsl = tsl0 - tsl0 * 0.1;
        else{
            tsr = tsr0;
            tsl = tsl0;
        }
#endif
    }
    else if(LEFTWALL)
    {
#ifndef KTRACKING
        slError = LIDEAL - sl;
        tsr = tsr0*(1.0+kP_TRACKING*(double)slError);
        tsl = tsl0*(1.0-kP_TRACKING*(double)slError);
#else
        if(sl < LIDEAL - KERROR) //right of center
            tsl = tsr0 - tsr0 * 0.1;
        else if(sl > LIDEAL + KERROR) //left of center
            tsr = tsl0 - tsl0 * 0.1;
        else{
            tsr = tsr0;
            tsl = tsl0;
        }
#endif
    }
    else{
        tsr = tsr0;
        tsl = tsl0;
    }
}
void mapWalls()
{
    rightWall = RIGHTWALL;
    leftWall = LEFTWALL;
    frontWall = FRONTWALL;
}
int sensorRead(int sensor)
{
    choose_sensor(sensor); //choose sensor
                            //optional noise read here
    emitterOn(sensor);
    __delay_us(5);
    AD1CON1bits.SAMP = 1; //Begin sample
    __delay_us(10);
    AD1CON1bits.SAMP = 0; //Stop sample
    emitterOff(sensor);
    while(!AD1CON1bits.DONE); //wait for conversion
    return ADC1BUF0; //read buffer
}
void emitterOn(int sensor)
{
    switch(sensor){
        case FLD:
            FLE = 1;
            break;
        case SLD:
            SLE = 1;
            break;
        case FRD:
            FRE = 1;
            break;
        case SRD:
            SRE = 1;
            break;
    }
}
void emitterOff(int sensor)
{
    switch(sensor){
        case FLD:
            FLE = 0;
            break;
        case SLD:
            SLE = 0;
            break;
        case FRD:
            FRE = 0;
            break;
        case SRD:
            SRE = 0;
            break;
    }
}
void choose_sensor(int sensor)
{
    AD1CHS0bits.CH0SA = sensor;     // Select senosor here.
}
void sensorStart()
{
    while(!FRONTSTOP);
    delayms(1000);
}
void initADC()
{	
    AD1CON1bits.ADON = 0;       // ADC Module Must be disable prior to config
    AD1CON1bits.AD12B = 0;      // 10-bit 4-Channel ADC Operation Mode
    AD1CON1bits.FORM = 0;       // Unsigned Integer Output (FORM <1:0>)
    AD1CON1bits.ASAM = 0;       // Automatic sampling disabled, controlled by software

    
    AD1CON2bits.VCFG = 0;       // VREFH=Avdd, VREFL=Avss (VCFG <2:0>)
    AD1CON2bits.CHPS = 0;       // Samples on CH0 (CHPS <1:0>)
    //AD1CON2bits.SMPI = 1;       // Interrupts on 1st Sample (SMPI <3:0>)
    AD1CON2bits.ALTS = 0;       // Always use MUXA Input Select
    AD1CON2bits.BUFM = 1;       // Dual 16-bit Buffer

    
    // ADC Configuration for 1.1 Msps
    // ADC Clock Period (TAD) = TCY(ADCS + 1) = 75ns
    // ADCS = TAD/TCY - 1
    AD1CON3bits.ADRC = 0;           // Use Instruction Clock Cycle (ADRC <0>)
    AD1CON3bits.ADCS = 2;           // Set ADCS Control bits (ADCS <7:0>)
	
	AD1CON1bits.ADON = 1;
	

}
void FR_Noise_Read()
{
    AD1CON1bits.SAMP = 1; //Begin sampling
    __delay_us(10);
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);
    noise = ADC1BUF0;
}
void delayms(int ms)
{
    int i;
    for(i=0;i<ms;i++)
        __delay_us(1000);
}
