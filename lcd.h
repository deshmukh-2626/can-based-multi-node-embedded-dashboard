#include "types.h"

void writeLCD(u8 byte);              

void cmdLCD(u8 byte);

void InitLCD(void);

void charLCD(u8 ascii);

void strLCD(s8 *);

void u32LCD(u32);

void s32LCD(s32);

void setcursor(u8,u8);

void f32LCD(f32 fnum, u32 point);
void Display5BarFuel(u8 percentage);
void DisplayVerticalFuel(u8 fuel_percent);
