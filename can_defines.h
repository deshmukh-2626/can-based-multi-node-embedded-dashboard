//TD1 CAN1_TX pin no alternate function,default
#define TD1_PIN       
//define p0.25 as RD1(i.e CAN1_RX)
#define RD1_PIN_0_25   


//#define PCLK          15000000  //Hz
#define BIT_RATE      125000    //Hz
#define QUANTA        20
#define BRP           (PCLK/(BIT_RATE*QUANTA))
#define SAMPLE_POINT  (0.7 * QUANTA)
#define TSEG1        	((u32)SAMPLE_POINT-1)
#define TSEG2        	(QUANTA-(1+TSEG1))	
#define SJW           ((TSEG2>=5)?4:(TSEG2-1))

//cfg values for CxBTR sfr
#define SAM         0 //0/1,sample bus 1/3 time(s)
#define BTR_LVAL 	(SAM<<23| \
                  ((TSEG2-1)<<20)| \
                  ((TSEG1-1)<<16)| \
                  ((SJW-1)<<14)|   \
									(BRP-1))

//CxCMR sfr bit defines
#define TR_BIT   0
#define RRB_BIT  2 
#define STB1_BIT 5

//CxGSR sfr bit defines
#define RBS_BIT  0
#define TBS1_BIT 2
#define TCS1_BIT 3

//CxTFI1/CxRFS sfr bit defines
#define RTR_BIT  30
#define DLC_BITS 16

//CxMOD sfr bit defines
#define RM_BIT   0

//AFMR sfr bit defines
#define AccOFF_BIT 0
#define AccBP_BIT  1
