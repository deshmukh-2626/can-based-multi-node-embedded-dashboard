#ifndef _ADC_H_

#define _ADC_H_


#include "types.h"

void Init_ADC(void);

f32 Read_ADC(u8 chNo);


#endif



void adc_init(void);
u32 read_adc(void);
