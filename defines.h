#ifndef _DEFINES_H
#define _DEFINES_H

#include "types.h"

// Single-bit Set and Clear
#define SSETBIT(WORD,BITPOS) (WORD = 1<<BITPOS)
#define SCLRBIT(WORD,BITPOS) (WORD &= ~(1<<BITPOS))  // FIXED

// Multi-bit Set, Clear, Toggle
#define SETBIT(WORD,BITPOS)  (WORD |= (1<<BITPOS))
#define CLRBIT(WORD,BITPOS)  (WORD &= ~(1<<BITPOS))
#define CPLBIT(WORD,BITPOS)  (WORD ^= (1<<BITPOS))

// Read Operations
#define READBIT(WORD,BITPOS)      ((WORD>>BITPOS)&1)
#define READNIBBLE(WORD,SBITPOS)  ((WORD>>SBITPOS)&15)
#define READBYTE(WORD,SBITPOS)    ((WORD>>SBITPOS)&255)

// Write Operations
#define WRITEBIT(WORD,BITPOS,BITVAL) \
    (WORD = ((WORD & ~(1<<BITPOS)) | (BITVAL<<BITPOS)))

#define WRITENIBBLE(WORD,SBITPOS,NIBBLE) \
    (WORD = ((WORD & ~(15<<SBITPOS)) | (NIBBLE<<SBITPOS)))

#define WRITEBYTE(WORD,STARTBITPOS,BYTE) \
    (WORD = ((WORD & ~((u32)0xFF<<STARTBITPOS)) | (BYTE<<STARTBITPOS)))

#endif
