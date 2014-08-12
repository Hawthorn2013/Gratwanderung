/* hehelight 看什么看！赛道灯而已！ */

#define __HEHELIGHT_C_
#include "includes.h"

/*-----------------------------------------------------------------------*/
/* 初始化赛道灯                                                         */
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
	SIU.PCR[12].R = 0x0203;   /* PA12 */
 	SIU.PCR[13].R = 0x0203;   /* PA13 */
  	SIU.PCR[14].R = 0x0203;   /* PA14 */
 	SIU.PCR[15].R = 0x0203;   /* PA15 */
 	
 	SIU.PCR[16].R = 0x0203;     /* PB0  */
  	SIU.PCR[17].R = 0x0203;     /* PB1  */
 	SIU.PCR[26].R = 0x0203;     /* PB10*/
	SIU.PCR[27].R = 0x0203;     /* PB11*/
 	SIU.PCR[28].R = 0x0203;     /* PB12*/
  	SIU.PCR[29].R = 0x0203;     /* PB13*/
 	SIU.PCR[30].R = 0x0203;     /* PB14*/
 	
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
	SIU.GPDO[12].R = 1;  //D0~3 1灭0亮
	SIU.GPDO[13].R = 1;
	SIU.GPDO[14].R = 1;
	SIU.GPDO[15].R = 1;
	
	SIU.GPDO[16].R = 0;	/* 0=熄灭 */
	SIU.GPDO[17].R = 0;
	SIU.GPDO[26].R = 0;
	SIU.GPDO[27].R = 0;
	SIU.GPDO[28].R = 0;
	SIU.GPDO[29].R = 0;
	SIU.GPDO[30].R = 0;
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