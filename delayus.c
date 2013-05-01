#include "p33FJ128MC804.h"
#include "delayus.h"

/*This is part of the project*/
void delayus(unsigned int delay)
{
    int i;
    for(i=0;i<delay;i++)
    {
        __asm__ volatile ("repeat #39");
        __asm__ volatile ("nop");
    }
}