#include "clock.h"
#include "p33FJ128MC804.h"

void init_OSC(void)
{
	// Clock Config
	PLLFBD=41;						// PLL Multiplier 9 bits {actual is N+2} (43) M
	CLKDIVbits.DOZE=0b000;		// Clock Reduction (divide by 1)
	CLKDIVbits.DOZEN=0b1;		// Doze Mode Enable (Use DOZE)
	CLKDIVbits.PLLPOST=0b00;		// PLL Post Output Divider (divide by 2) N2
	CLKDIVbits.PLLPRE=0b00000;			// PLL input divider (divide by 2) N1

	/* 80 MHz -> running 40 MIPS */
}



