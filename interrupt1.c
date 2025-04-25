                   /* external_interrupts_test2.c */

#include <lpc21xx.h>
#include "defines.h"

#include "pin_function_defines.h"


#include "interrupt.h"

#include "delay.h"
#include "can.h"


//unsigned int count;


extern int flag1, flag2;
CANF txF;

void eint0_isr(void) __irq

{

    flag1 = 1;               // Set flag to indicate ISR executed
    txF.ID = 2;
    txF.BFV.RTR = 0;
    txF.BFV.DLC = 1;
	if(((IOPIN0>>16)&1)==0){
		txF.Data1 = 'L';         // Send 'B' (ASCII 66)
    	txF.Data2 = 0;
	}
    CAN1_Tx(txF);            // Send CAN frame
  //  count2++;                // Default task of ISR
    EXTINT = 0x0;            // Clear EINT0 interrupt flag
    VICVectAddr = 0x0;       // End of ISR


}


void eint1_isr(void) __irq

{

    flag2 = 1;               // Set flag to indicate ISR executed
    txF.ID = 2;
    txF.BFV.RTR = 0;
    txF.BFV.DLC = 1;
	if(((IOPIN0>>14)&1)==0){
		txF.Data1 = 'R';         // Send 'B' (ASCII 66)
    	txF.Data2 = 0;
	}
    CAN1_Tx(txF);            // Send CAN 
    //count2++;                // Default task of ISR
    EXTINT = 0x1;            // Clear EINT1 interrupt flag
    VICVectAddr = 0x0;       // End of ISR

}	

	


void Enable_EINT0(void)

{

	CFGPIN(PINSEL0,1,FUNC4);

//	SETBIT(IODIR0,EINT0_LED);

	SSETBIT(VICIntEnable,14);

	VICVectCntl0=0x20|14;

	VICVectAddr0=(unsigned)eint0_isr;

	SCLRBIT(EXTINT,0);

 	SETBIT(EXTMODE,0);

  	SETBIT(EXTPOLAR,0);

}


void Enable_EINT1(void)

{

	CFGPIN(PINSEL0,3,FUNC4);

//	SETBIT(IODIR0,EINT1_LED);

	SSETBIT(VICIntEnable,15);

	VICVectCntl1=0x20|15;

	VICVectAddr1=(unsigned)eint1_isr;

	SCLRBIT(EXTINT,1);

	SETBIT(EXTMODE,1);

  	SETBIT(EXTPOLAR,1);	

}

