#include <LPC21xx.H>
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"

s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

void RTC_Init(void)
{
	//reset the CTC SFR 
	CCR = RTC_CTC_RST;
	//init. 1sec tick rate by using prescalar registers
	PREINT = PREINT_Val;
	PREFRAC = PREFRAC_Val;
	//enable the timer
	CCR = RTC_CCR_EN;
}

void GetRTCTime(s32 *hr,s32 *mi,s32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;
}

void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
		//setcursor(1,0);
		cmdLCD(0x0C);
		charLCD((hour/10)+48);
		charLCD((hour%10)+48);
		charLCD(':');
		charLCD((min/10)+48);
		charLCD((min%10)+48);
		charLCD(':');
		charLCD((sec/10)+48);
		charLCD((sec%10)+48);	
}

void GetRTCDate(s32 *date,s32 *mon,s32 *year)
{
	*date = DOM;
	*mon = MONTH;
	*year = YEAR;
}

void DisplayRTCDate(u32 date,u32 month,u32 year)
{
		//setcursor(2,0);
		charLCD((date/10)+48);
		charLCD((date%10)+48);
		charLCD('/');
		charLCD((month/10)+48);
		charLCD((month%10)+48);
		charLCD('/');
		s32LCD(year);	
}

void SetRTCTime(u32 hour,u32 min,u32 sec)
{
	HOUR = hour;
	MIN = min;
	SEC = sec;
}

void SetRTCDate(u32 date,u32 month,u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

void GetRTCDay(s32 *day)
{
	*day = DOW;
}

void DisplayRTCDay(u32 day)
{
	setcursor(2,15);
	strLCD(week[day]);
}

void SetRTCDay(u32 day)
{
	DOW = day;
}
