#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H
#include "adc_defines.h"

#define PREINT_Val ((int) ((PCLK/32768) - 1))
#define PREFRAC_Val (PCLK - ((PREINT_Val+1)*32768))

#define RTC_CTC_RST (1<<1)
#define RTC_CCR_EN  (1<<0)

#endif
