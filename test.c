#include "p33FJ128MC802.h"
#include "interrupts.h"
#include "QEI.h"
#include "sensors.h"
#include "libpic30.h"
#include "delay.h"
#include "configports.h"
#include "movement.h"
#include "clock.h"
#include "pwm.h"
#include "maze.h"
#include "queue.h"
#include "cell.h"
#include "mouse.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Configuration Bits ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
_FBS(RBS_NO_RAM&BSS_NO_BOOT_CODE&BWRP_WRPROTECT_OFF);
_FSS(RSS_NO_RAM&SSS_NO_FLASH&SWRP_WRPROTECT_OFF);
_FGS(GSS_OFF&GCP_OFF&GWRP_OFF);
_FOSCSEL(FNOSC_FRCPLL&IESO_OFF);
_FOSC(FCKSM_CSDCMD&IOL1WAY_OFF&OSCIOFNC_ON&POSCMD_NONE);
_FWDT(FWDTEN_OFF&WINDIS_OFF&WDTPRE_PR128&WDTPOST_PS32768 );
_FPOR(PWMPIN_ON&HPOL_OFF&LPOL_ON&ALTI2C_OFF&FPWRT_PWR128 );
_FICD(JTAGEN_OFF&ICS_PGD2);

//#define TEST
//#define WALLHUG

extern double rDispTotal, lDispTotal;
extern double targetDist;
extern double tsr0, tsl0, tsr, tsl;
extern int fr, fl, sr, sl;
extern int tracking, mapping, turning;
extern int rightWall, leftWall, frontWall;
    Cell maze[16][16];
    int x,y,dir;
    int returnRun = 0;

int main(void)
{
//    int i;
    rDispTotal = lDispTotal = targetDist = 0;

    x = 0;
    y = 0;
    dir = NORTH;

    m_init(maze);


    config_ports(); //set ports

    init_OSC();     //Initialize Oscillator

    initADC();    //Initialize ADC

    init_QEI();    //Initialize QEI for right motor

    initPWM();    //Initialize PWM

    brake();


    enable_T1();    //Enable Timer 1 for QEI calcs
    enable_T2();

    sensorStart();
    tsr0 = tsl0 = tsr = tsl = CELL*1.5;
//    moving = 0;
    turning = 0;
    mapWalls();

#ifndef TEST
#ifndef WALLHUG
    mapping = 1;
    while(1){
        update(maze,x,y,dir);
        flood2center(maze);
        returnRun = 0;
        while(!inCenter(x,y)){
//            update(maze,x,y,dir);
//            flood2center(maze);
            move(maze,&x,&y,&dir);
        }
        returnRun = 1;
        while(!inStart(x,y)){
//            update(maze,x,y,dir);
//            flood2start(maze);
            move(maze,&x,&y,&dir);
        }
    }
#else
    mapping = 0;
    while(1){
        if(!rightWall){
            right90();
            cellForward(1);
        }
        else if(!frontWall){
            cellForward(1);
        }
        else if(!leftWall){
            left90();
            cellForward(1);
        }
        else{
            aboutFace();
            cellForward(1);
        }
    }
#endif
#else
//    for(i=0;i<5;i++)
        right90();
    while(1);
#endif
}
