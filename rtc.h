#ifndef _RTC_H
#define _RTC_H

#include "types.h"

void RTC_Init(void);
void GetRTCTime(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDate(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void SetRTCTime(u32,u32,u32);
void SetRTCDate(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);

#endif
