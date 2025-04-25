#include <LPC21xx.H>
#include "types.h"
#include "defines.h"
#include "can.h"
#include"lcd.h"
#include "delay.h"

#define EINT0_PIN 16
#define EINT1_PIN 14

extern CANF txF;
extern u32 flag1, flag2;
u32 cnt=0;
	int i;
u8 left_blink = 0;
u8 right_blink = 0;



void EINT0_Handler(void) __irq {
    flag1 = 1;

    txF.ID = 2;
    txF.BFV.RTR = 0;
    txF.BFV.DLC = 1;

    if (((IOPIN0 >> EINT0_PIN) & 1) == 0) {
        txF.Data1 = 76;  // 'L'
        txF.Data2 = 0;
        CAN1_Tx(txF);

        // Toggle left blinking
        if (left_blink == 0) {
            left_blink = 1;
            right_blink = 0;
        } else {
            left_blink = 0;
        }
    }

    EXTINT |= (1 << 0);  // Clear EINT0
    VICVectAddr = 0x0;
}



void EINT1_Handler(void) __irq {
    flag2 = 1;

    txF.ID = 2;
    txF.BFV.RTR = 0;
    txF.BFV.DLC = 1;

    if (((IOPIN0 >> EINT1_PIN) & 1) == 0) {
        txF.Data1 = 82;  // 'R'
        txF.Data2 = 0;
        CAN1_Tx(txF);

        // Toggle right blinking
        if (right_blink == 0) {
            right_blink = 1;
            left_blink = 0;
        } else {
            right_blink = 0;
        }
    }

    EXTINT |= (1 << 1);  // Clear EINT1
    VICVectAddr = 0x0;
}

void config_vic(void) {
    VICIntSelect = 0x0;       // Configure as IRQ (not FIQ)

    VICVectCntl0 = 14 | (1 << 5);  // Assign EINT0 to IRQ slot 0
    VICVectAddr0 = (u32)EINT0_Handler;

    VICVectCntl1 = 15 | (1 << 5);  // Assign EINT1 to IRQ slot 1
    VICVectAddr1 = (u32)EINT1_Handler;

    VICIntEnable |= (1 << 14); // Enable EINT0
    VICIntEnable |= (1 << 15); // Enable EINT1
}

void config_eint(void) {
    // Configure P0.16 as EINT0
    PINSEL1 |= (1 << 0);  // P0.16 as EINT0

    // Configure P0.14 as EINT1
    PINSEL0 |= (2 << 28); // P0.14 as EINT1 (bits 28-29)

    // Set both EINT0 and EINT1 as edge-triggered
    EXTMODE = 0x3;          // Both EINT0 & EINT1 are edge-triggered

    // Set both to falling edge triggered
    EXTPOLAR = 0x0;         // Both are active low
}


void Enable_EINT1(void) {
    config_eint(); // Configure the pins first

    // Set interrupt priority for EINT1
    VICIntEnable |= (1 << 15);
    VICVectCntl1 = 0x20 | 15;
    VICVectAddr1 = (u32)EINT1_Handler;
}


void Enable_EINT0(void) {
    config_eint(); // Configure the pins first

    // Set interrupt priority for EINT0
    VICIntEnable |= (1 << 14);
    VICVectCntl0 = 0x20 | 14;
    VICVectAddr0 = (u32)EINT0_Handler;
}

