#include "sensors.h"
#include "p33FJ128MC804.h"
#include "libpic30.h"
#include "delay.h"
#include "clock.h"
#include "led.h"

int noise;
extern double tsr, tsl, tsr0, tsl0;
extern int fl,sl,fr,sr;
extern int rDispTotal,lDispTotal;
int rightWall = 0;
int leftWall = 0;
int frontWall = 0;
int srError,slError;
int srErrorPrev,slErrorPrev;

//tracking gains
#define kP_TRACKING 0.003
#define kD_TRACKING 0.002

#define SRERROR_DIFF (double)(srError-srErrorPrev)
#define SLERROR_DIFF (double)(slError-slErrorPrev)

void track()
{
    double correction;

    sl = sensorRead(SLD);
    if(LEFTWALL_T){
        srErrorPrev = srError = 0;
        slErrorPrev = slError;
        slError = LIDEAL - sl;
        if(slErrorPrev > 0)
            correction = kP_TRACKING*slError + kD_TRACKING*SLERROR_DIFF;
        else
            correction = kP_TRACKING*slError;

        tsr = tsr0*(1.0+correction);
        tsl = tsl0*(1.0-correction);
        return;
    }

    sr = sensorRead(SRD);
    if(RIGHTWALL_T){
        slErrorPrev = slError = 0;
        srErrorPrev = srError;
        srError = RIDEAL - sr;

        if(srErrorPrev > 0)
            correction = kP_TRACKING*(double)srError + kD_TRACKING*(double)SRERROR_DIFF;
        else
            correction = kP_TRACKING*(double)srError;

        tsr = tsr0*(1.0-correction);
        tsl = tsl0*(1.0+correction);
        return;
    }

    tsr = tsr0;
    tsl = tsl0;
    slError = srError = srErrorPrev = slErrorPrev = 0;
}
void mapWalls()
{
    fl = sensorRead(FLD);
    fr = sensorRead(FRD);
    sl = sensorRead(SLD);
    sr = sensorRead(SRD);
    rightWall = RIGHTWALL;
    leftWall = LEFTWALL;
    frontWall = FRONTWALL;
    RED = leftWall;
    BLUE = frontWall;
    GREEN = rightWall;
}
int sensorRead(int sensor)
{
    int noise;
    choose_sensor(sensor); //choose sensor

    //noise reading
    AD1CON1bits.SAMP = 1; //Begin sample
    __delay_us(10);
    AD1CON1bits.SAMP = 0; //Stop sample
    while(!AD1CON1bits.DONE); //wait for conversion
    noise = ADC1BUF0; //read buffer

    emitterOn(sensor);
    __delay_us(5);
    AD1CON1bits.SAMP = 1; //Begin sample
    __delay_us(10);
    AD1CON1bits.SAMP = 0; //Stop sample
    emitterOff(sensor);
    while(!AD1CON1bits.DONE); //wait for conversion
    return ADC1BUF0-noise; //read buffer
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
    ledYellow();
    fl = sensorRead(FLD);
    fr = sensorRead(FRD);
    while(!FRONTSTOP){
        fl = sensorRead(FLD);
        fr = sensorRead(FRD);
    }
    ledGreen();
    delayms(1000);
    rDispTotal = lDispTotal = 0;
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
