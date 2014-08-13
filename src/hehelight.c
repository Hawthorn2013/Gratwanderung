/* hehelight 看什么看！赛道灯而已！ */

#define __HEHELIGHT_C_
#include "includes.h"

/*-----------------------------------------------------------------------*/
/* 初始化赛道灯                                                                      */
/*-----------------------------------------------------------------------*/
void init_hehelight(void)
{
 	SIU.PCR[0].R = 0x0203;	   /* PA0  */
  	SIU.PCR[1].R = 0x0203;     /* PA1  */
 	SIU.PCR[2].R = 0x0203;     /* PA2  */
 	
	SIU.PCR[4].R = 0x0203;	   /* PA4  */
 	SIU.PCR[5].R = 0x0203;	   /* PA5  */
  	SIU.PCR[6].R = 0x0203;     /* PA6  */
 	SIU.PCR[7].R = 0x0203;     /* PA7  */
 	SIU.PCR[8].R  = 0x0203;	   /* PA8   */
 	
  	SIU.PCR[10].R = 0x0203;   /* PA10 */
 	SIU.PCR[11].R = 0x0203;   /* PA11 */
 	
 	SIU.PCR[16].R = 0x0203;     /* PB0  */
  	SIU.PCR[17].R = 0x0203;     /* PB1  */
  	
 	SIU.PCR[26].R = 0x0203;     /* PB10*/
	SIU.PCR[27].R = 0x0203;     /* PB11*/
 	SIU.PCR[28].R = 0x0203;     /* PB12*/
  	SIU.PCR[29].R = 0x0203;     /* PB13*/
 	SIU.PCR[30].R = 0x0203;     /* PB14*/
	SIU.PCR[31].R = 0x0203;
 	SIU.PCR[32].R = 0x0203;
  	SIU.PCR[33].R = 0x0203;
  	
 	SIU.PCR[35].R = 0x0203; 
 	
 	
	SIU.GPDO[0].R = 0;	       /* 0=熄灭 */
	SIU.GPDO[1].R = 0;
	SIU.GPDO[2].R = 0;
	
	SIU.GPDO[4].R = 0;
	SIU.GPDO[5].R = 0;
	SIU.GPDO[6].R = 0;
	SIU.GPDO[7].R = 0;
	SIU.GPDO[8].R = 0; 	/* 0=熄灭 */
	SIU.GPDO[10].R = 0;
	SIU.GPDO[11].R = 0;
	
	SIU.GPDO[16].R = 0;	/* 0=熄灭 */
	SIU.GPDO[17].R = 0;
	
	SIU.GPDO[26].R = 0;
	SIU.GPDO[27].R = 0;
	SIU.GPDO[28].R = 0;
	SIU.GPDO[29].R = 0;
	SIU.GPDO[30].R = 0;
	SIU.GPDO[31].R = 1;
	SIU.GPDO[32].R = 1;
	SIU.GPDO[33].R = 1;
	
	SIU.GPDO[35].R = 1;
}

/*-----------------------------------------------------------------------*/
/* 点亮全部赛道灯                                                         */
/*-----------------------------------------------------------------------*/

void hehelighton(void)
{
	SIU.GPDO[0].R = 1;	   
	SIU.GPDO[1].R = 1;
	SIU.GPDO[2].R = 1;
	SIU.GPDO[4].R = 1;
	SIU.GPDO[5].R = 1;
	SIU.GPDO[6].R = 1;
	SIU.GPDO[7].R = 1;
	
	SIU.GPDO[8].R = 1; 
	SIU.GPDO[10].R = 1;
	SIU.GPDO[11].R = 1;
	SIU.GPDO[12].R = 1;
	SIU.GPDO[13].R = 1;
	SIU.GPDO[14].R = 1;
	SIU.GPDO[15].R = 1;
	
	SIU.GPDO[16].R = 1;
	SIU.GPDO[17].R = 1;
	SIU.GPDO[26].R = 1;
	SIU.GPDO[27].R = 1;
	SIU.GPDO[28].R = 1;
	SIU.GPDO[29].R = 1;
	SIU.GPDO[30].R = 1;	
}

/*-----------------------------------------------------------------------*/
/* 熄灭全部赛道灯                                                         */
/*-----------------------------------------------------------------------*/

void hehelightoff(void)
{
	SIU.GPDO[0].R = 0;	       /* 0=熄灭 */
	SIU.GPDO[1].R = 0;
	SIU.GPDO[2].R = 0;
	SIU.GPDO[4].R = 0;
	SIU.GPDO[5].R = 0;
	SIU.GPDO[6].R = 0;
	SIU.GPDO[7].R = 0;
	
	SIU.GPDO[8].R = 0; 	/* 0=熄灭 */
	SIU.GPDO[10].R = 0;
	SIU.GPDO[11].R = 0;
	SIU.GPDO[12].R = 0;
	SIU.GPDO[13].R = 0;
	SIU.GPDO[14].R = 0;
	SIU.GPDO[15].R = 0;
	
	SIU.GPDO[16].R = 0;	/* 0=熄灭 */
	SIU.GPDO[17].R = 0;
	SIU.GPDO[26].R = 0;
	SIU.GPDO[27].R = 0;
	SIU.GPDO[28].R = 0;
	SIU.GPDO[29].R = 0;
	SIU.GPDO[30].R = 0;
}


void init_hehelight_PWM(void)
{
	/* Modulus Up Counter 50HZ */
	EMIOS_0.CH[0].CCR.B.UCPRE=0;	/* Set channel prescaler to divide by 4 */
	EMIOS_0.CH[0].CCR.B.UCPEN = 1;	/* Enable prescaler; uses default divide by 4 */
	EMIOS_0.CH[0].CCR.B.FREN = 1;	/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[0].CADR.R = 2500;	/* 设置周期0.02s  50HZ */
	EMIOS_0.CH[0].CCR.B.MODE = 0x50;	/* Modulus Counter Buffered (MCB) */
	EMIOS_0.CH[0].CCR.B.BSL = 0x3;	/* Use internal counter */
	
	/* PA1 */
	EMIOS_0.CH[1].CCR.B.BSL = 0x1;
	EMIOS_0.CH[1].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[1].CCR.B.EDPOL = 1;
	EMIOS_0.CH[1].CADR.R = 0;
	EMIOS_0.CH[1].CBDR.R = 0;
	SIU.PCR[1].R = 0x0600;
	
	/* PA2 */
	EMIOS_0.CH[2].CCR.B.BSL = 0x1;
	EMIOS_0.CH[2].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[2].CCR.B.EDPOL = 1;
	EMIOS_0.CH[2].CADR.R = 0;
	EMIOS_0.CH[2].CBDR.R = 0;
	SIU.PCR[2].R = 0x0600;
	
	/* PB11 */
	EMIOS_0.CH[3].CCR.B.BSL = 0x1;
	EMIOS_0.CH[3].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[3].CCR.B.EDPOL = 1;
	EMIOS_0.CH[3].CADR.R = 0;
	EMIOS_0.CH[3].CBDR.R = 0;
	SIU.PSMI[13].R = 1;
	SIU.PCR[27].R = 0x0600;
	
	/* PA4 */
	EMIOS_0.CH[4].CCR.B.BSL = 0x1;
	EMIOS_0.CH[4].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[4].CCR.B.EDPOL = 1;
	EMIOS_0.CH[4].CADR.R = 0;
	EMIOS_0.CH[4].CBDR.R = 0;
	SIU.PCR[4].R = 0x0600;
	
	/* PA5 */
	EMIOS_0.CH[5].CCR.B.BSL = 0x1;
	EMIOS_0.CH[5].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[5].CCR.B.EDPOL = 1;
	EMIOS_0.CH[5].CADR.R = 0;
	EMIOS_0.CH[5].CBDR.R = 0;
	SIU.PCR[5].R = 0x0600;
	
	/* PA6 */
	EMIOS_0.CH[6].CCR.B.BSL = 0x1;
	EMIOS_0.CH[6].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[6].CCR.B.EDPOL = 1;
	EMIOS_0.CH[6].CADR.R = 0;
	EMIOS_0.CH[6].CBDR.R = 0;
	SIU.PCR[6].R = 0x0600;
	
	/* PA7 */
	EMIOS_0.CH[7].CCR.B.BSL = 0x1;
	EMIOS_0.CH[7].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[7].CCR.B.EDPOL = 1;
	EMIOS_0.CH[7].CADR.R = 0;
	EMIOS_0.CH[7].CBDR.R = 0;
	SIU.PCR[7].R = 0x0600;
	
	/* 另外一路 */
	
	/* PA10 */
	EMIOS_0.CH[10].CCR.B.BSL = 0x1;
	EMIOS_0.CH[10].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[10].CCR.B.EDPOL = 1;
	EMIOS_0.CH[10].CADR.R = 0;
	EMIOS_0.CH[10].CBDR.R = 0;
	SIU.PCR[10].R = 0x0600;
	
	/* PA11 */
	EMIOS_0.CH[11].CCR.B.BSL = 0x1;
	EMIOS_0.CH[11].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[11].CCR.B.EDPOL = 1;
	EMIOS_0.CH[11].CADR.R = 0;
	EMIOS_0.CH[11].CBDR.R = 0;
	SIU.PCR[11].R = 0x0600;
	
	/* PC12 */
	EMIOS_0.CH[12].CCR.B.BSL = 0x1;
	EMIOS_0.CH[12].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[12].CCR.B.EDPOL = 1;
	EMIOS_0.CH[12].CADR.R = 0;
	EMIOS_0.CH[12].CBDR.R = 0;
	SIU.PCR[44].R = 0x0600;
	
	/* PC13 */
	EMIOS_0.CH[13].CCR.B.BSL = 0x1;
	EMIOS_0.CH[13].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[13].CCR.B.EDPOL = 1;
	EMIOS_0.CH[13].CADR.R = 0;
	EMIOS_0.CH[13].CBDR.R = 0;
	SIU.PCR[45].R = 0x0600;
	
	/* PC14 */
	EMIOS_0.CH[14].CCR.B.BSL = 0x1;
	EMIOS_0.CH[14].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[14].CCR.B.EDPOL = 1;
	EMIOS_0.CH[14].CADR.R = 0;
	EMIOS_0.CH[14].CBDR.R = 0;
	SIU.PCR[46].R = 0x0600;
	
	/* PC15 */
	EMIOS_0.CH[15].CCR.B.BSL = 0x1;
	EMIOS_0.CH[15].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[15].CCR.B.EDPOL = 1;
	EMIOS_0.CH[15].CADR.R = 0;
	EMIOS_0.CH[15].CBDR.R = 0;
	SIU.PCR[47].R = 0x0600;
}