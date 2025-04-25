/*adc0_driver.c*/
#include<LPC21XX.H>
#include "types.h"
#include "adc_defines.h"
#include "defines.h"
#include "delay.h"


void Init_ADC(void)

{
  PINSEL1|=0X15400000;
  ADCR=PDN_BIT|CLKDIV|CHANNEL_SEL;	

}


f32 Read_ADC(u8 chNo)

{

  u16 adcVal=0;

	f32 eAR;

	WRITEBYTE(ADCR,0,chNo);

	SETBIT(ADCR,ADC_START_BIT);

	delay_us(3);

	while(!READBIT(ADDR,DONE_BIT));

	CLRBIT(ADCR,ADC_START_BIT);

	adcVal=(ADDR>>6)&0x3FF;

	eAR=((adcVal*3.3)/1023);

	return eAR;

}




void adc_init(void){
    //PINSEL1|=(1<<24); //P0.4 becomes AD0.6
    ADCR = 0x00200440; //channel 6 selected
                        //CLKDIV=5 (ADC0 frequency is 3MHz)
                        //BURST=
                        //Resolution(accuracy)=10bits
                        //Power down mode=off
                        //ADC0 is off(initially)
}

u32 read_adc(void){
    //It reads 10bit value thus we can return either u32 or u16
    u32 temp;
    ADCR|=(1<<24); //start ADC conversion
    //while(((ADDR6>>31)&1)==0);
    while(((ADDR>>31)&1)==0);
    ADCR&=~(1<<24); //stop ADC conversion
    //temp=(AD0DR6>>6)&0x3ff;
    temp=(ADDR>>6)&0x3ff; //masking last 10bits of temp, 
                                //temp will look like 00000000 00000000 00000011 11111111 initially    
    return temp;
}
