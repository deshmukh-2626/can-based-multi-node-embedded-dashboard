#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "can_defines.h"
#include "adc_defines.h"
#include "can.h"

void Init_CAN1(void)
{
    //cfg p0.25 as CAN1_RX pin(RD1)
    PINSEL1|=0x00040000;
    //Reset CAN1 controller
    SETBIT(C1MOD,RM_BIT);		
    //all received messages are accepted
	 CLRBIT(AFMR,AccOFF_BIT);
    SETBIT(AFMR,AccBP_BIT);             
	  //AFMR=((AFMR&~(3<<AccOFF_BIT))|(2<<AccOFF_BIT));
    //Set baud Rate for CAN
    C1BTR=BTR_LVAL;
   //Enable CAN1 controller
    CLRBIT(C1MOD,RM_BIT);					
}

// Transmit CAN frame with a check for transmission failure
void CAN1_Tx(CANF txFrame)
{
    // Define a timeout counter (you can adjust the number of attempts)
    int timeout_counter = 10000;  // Set an arbitrary large number for timeout

    // Wait for the TX buffer to be empty, but with a timeout to prevent getting stuck
    while (READBIT(C1GSR, TBS1_BIT) == 0)
    {
        timeout_counter--;
        if (timeout_counter <= 0)
        {
            // Timeout: Could not transmit frame, exit the function
            return;
        }
    }

    // Configure Tx ID
    C1TID1 = txFrame.ID;

    // Configure RTR and DLC
    C1TFI1 = (txFrame.BFV.RTR << RTR_BIT) | (txFrame.BFV.DLC << DLC_BITS);

    // If it's not a Remote frame (RTR = 0), write data to TX buffer
    if (txFrame.BFV.RTR != 1)
    {
        // Write data bytes 1-4
        C1TDA1 = txFrame.Data1;
        // Write data bytes 5-8
        C1TDB1 = txFrame.Data2;
    }

    // Select Tx Buff 1 & Start transmission
    C1CMR |= 1 << STB1_BIT | 1 << TR_BIT;

    // Wait until transmission is complete
    timeout_counter = 10000;  // Reset timeout for completion check
    while (READBIT(C1GSR, TCS1_BIT) == 0)
    {
        timeout_counter--;
        if (timeout_counter <= 0)
        {
            // Timeout: Transmission failed or taking too long, exit the function
            return;
        }
    }
}

void CAN1_Rx(CANF *rxFrame)
{
  //wait for CAN frame recv status
  while(READBIT(C1GSR,RBS_BIT)==0);
  //read 11-bit CANid of recvd frame.
  rxFrame->ID=C1RID; 
  //& read & extract data/remote frame status
  rxFrame->BFV.RTR=(C1RFS>>RTR_BIT)&1;
  //& extract data length
  rxFrame->BFV.DLC=(C1RFS>>DLC_BITS)&0x0f;
  //check if recvd frame is data frame,
  if(rxFrame->BFV.RTR==0)
  {	
   //extract data bytes 1-4
   rxFrame->Data1=C1RDA;
   //extract data bytes 5-8
   rxFrame->Data2=C1RDB;
  }
  // Release receive buffer command
  SETBIT(C1CMR,RRB_BIT);    
}
