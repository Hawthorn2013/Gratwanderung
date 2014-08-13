/* hehelight ��ʲô���������ƶ��ѣ� */

#define __HEHELIGHT_C_
#include "includes.h"


/*-----------------------------------------------------------------------*/
/* ��ʼ��������                                                                      */
/*-----------------------------------------------------------------------*/
void init_hehelight_PWM(void)
{
	/* Modulus Up Counter 50HZ */
	EMIOS_0.CH[23].CCR.B.UCPRE=0;	/* Set channel prescaler to divide by 4 */
	EMIOS_0.CH[23].CCR.B.UCPEN = 1;	/* Enable prescaler; uses default divide by 4 */
	EMIOS_0.CH[23].CCR.B.FREN = 1;	/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[23].CADR.R = 2500;	/* ��������0.02s  50HZ */
	EMIOS_0.CH[23].CCR.B.MODE = 0x50;	/* Modulus Counter Buffered (MCB) */
	EMIOS_0.CH[23].CCR.B.BSL = 0x3;	/* Use internal counter */

#if 0
	/* PA0 */
	/* �Ҳ���BUG�������ò��ˣ������ǵ�Ƭ���ͺŲ�ͬ */
	EMIOS_0.CH[0].CCR.B.BSL = 0x0;
	EMIOS_0.CH[0].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[0].CCR.B.EDPOL = 1;
	EMIOS_0.CH[0].CADR.R = 0;
	EMIOS_0.CH[0].CBDR.R = 0;
	SIU.PCR[0].R = 0x0600;
#endif

	/* PA1 */
	EMIOS_0.CH[1].CCR.B.BSL = 0x0;
	EMIOS_0.CH[1].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[1].CCR.B.EDPOL = 1;
	EMIOS_0.CH[1].CADR.R = 0;
	EMIOS_0.CH[1].CBDR.R = 0;
	SIU.PCR[1].R = 0x0600;
	
	/* PA2 */
	EMIOS_0.CH[2].CCR.B.BSL = 0x0;
	EMIOS_0.CH[2].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[2].CCR.B.EDPOL = 1;
	EMIOS_0.CH[2].CADR.R = 0;
	EMIOS_0.CH[2].CBDR.R = 0;
	SIU.PCR[2].R = 0x0600;
	
	/* PB11 */
	EMIOS_0.CH[3].CCR.B.BSL = 0x0;
	EMIOS_0.CH[3].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[3].CCR.B.EDPOL = 1;
	EMIOS_0.CH[3].CADR.R = 0;
	EMIOS_0.CH[3].CBDR.R = 0;
	SIU.PSMI[13].R = 1;
	SIU.PCR[27].R = 0x0600;
	
	/* PA4 */
	EMIOS_0.CH[4].CCR.B.BSL = 0x0;
	EMIOS_0.CH[4].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[4].CCR.B.EDPOL = 1;
	EMIOS_0.CH[4].CADR.R = 0;
	EMIOS_0.CH[4].CBDR.R = 0;
	SIU.PCR[4].R = 0x0600;
	
	/* PA5 */
	EMIOS_0.CH[5].CCR.B.BSL = 0x0;
	EMIOS_0.CH[5].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[5].CCR.B.EDPOL = 1;
	EMIOS_0.CH[5].CADR.R = 0;
	EMIOS_0.CH[5].CBDR.R = 0;
	SIU.PCR[5].R = 0x0600;
	
	/* PA6 */
	EMIOS_0.CH[6].CCR.B.BSL = 0x0;
	EMIOS_0.CH[6].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[6].CCR.B.EDPOL = 1;
	EMIOS_0.CH[6].CADR.R = 0;
	EMIOS_0.CH[6].CBDR.R = 0;
	SIU.PCR[6].R = 0x0600;
	
	/* PA7 */
	EMIOS_0.CH[7].CCR.B.BSL = 0x0;
	EMIOS_0.CH[7].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[7].CCR.B.EDPOL = 1;
	EMIOS_0.CH[7].CADR.R = 0;
	EMIOS_0.CH[7].CBDR.R = 0;
	SIU.PCR[7].R = 0x0600;
	
	/* ����һ· */
	
	/* PA10 */
	EMIOS_0.CH[10].CCR.B.BSL = 0x0;
	EMIOS_0.CH[10].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[10].CCR.B.EDPOL = 1;
	EMIOS_0.CH[10].CADR.R = 0;
	EMIOS_0.CH[10].CBDR.R = 0;
	SIU.PCR[10].R = 0x0600;
	
	/* PA11 */
	EMIOS_0.CH[11].CCR.B.BSL = 0x0;
	EMIOS_0.CH[11].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[11].CCR.B.EDPOL = 1;
	EMIOS_0.CH[11].CADR.R = 0;
	EMIOS_0.CH[11].CBDR.R = 0;
	SIU.PCR[11].R = 0x0600;
	
	/* PC12 */
	EMIOS_0.CH[12].CCR.B.BSL = 0x0;
	EMIOS_0.CH[12].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[12].CCR.B.EDPOL = 1;
	EMIOS_0.CH[12].CADR.R = 0;
	EMIOS_0.CH[12].CBDR.R = 0;
	SIU.PCR[44].R = 0x0600;
	
	/* PC13 */
	EMIOS_0.CH[13].CCR.B.BSL = 0x0;
	EMIOS_0.CH[13].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[13].CCR.B.EDPOL = 1;
	EMIOS_0.CH[13].CADR.R = 0;
	EMIOS_0.CH[13].CBDR.R = 0;
	SIU.PCR[45].R = 0x0600;
	
	/* PC14 */
	EMIOS_0.CH[14].CCR.B.BSL = 0x0;
	EMIOS_0.CH[14].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[14].CCR.B.EDPOL = 1;
	EMIOS_0.CH[14].CADR.R = 0;
	EMIOS_0.CH[14].CBDR.R = 0;
	SIU.PCR[46].R = 0x0600;
	
	/* PC15 */
	EMIOS_0.CH[15].CCR.B.BSL = 0x0;
	EMIOS_0.CH[15].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[15].CCR.B.EDPOL = 1;
	EMIOS_0.CH[15].CADR.R = 0;
	EMIOS_0.CH[15].CBDR.R = 0;
	SIU.PCR[47].R = 0x0600;
	
	/* PE0 */
	EMIOS_0.CH[16].CCR.B.BSL = 0x0;
	EMIOS_0.CH[16].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[16].CCR.B.EDPOL = 1;
	EMIOS_0.CH[16].CADR.R = 0;
	EMIOS_0.CH[16].CBDR.R = 0;
	SIU.PCR[64].R = 0x0600;
	
	/* PE1 */
	EMIOS_0.CH[17].CCR.B.BSL = 0x0;
	EMIOS_0.CH[17].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[17].CCR.B.EDPOL = 1;
	EMIOS_0.CH[17].CADR.R = 0;
	EMIOS_0.CH[17].CBDR.R = 0;
	SIU.PCR[65].R = 0x0600;
	
	/* PE2 */
	EMIOS_0.CH[18].CCR.B.BSL = 0x0;
	EMIOS_0.CH[18].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[18].CCR.B.EDPOL = 1;
	EMIOS_0.CH[18].CADR.R = 0;
	EMIOS_0.CH[18].CBDR.R = 0;
	SIU.PCR[66].R = 0x0600;
	
	/* PE4 */
	EMIOS_0.CH[20].CCR.B.BSL = 0x0;
	EMIOS_0.CH[20].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[20].CCR.B.EDPOL = 1;
	EMIOS_0.CH[20].CADR.R = 0;
	EMIOS_0.CH[20].CBDR.R = 0;
	SIU.PCR[68].R = 0x0600;
	
	/* PE5 */
	EMIOS_0.CH[21].CCR.B.BSL = 0x0;
	EMIOS_0.CH[21].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[21].CCR.B.EDPOL = 1;
	EMIOS_0.CH[21].CADR.R = 0;
	EMIOS_0.CH[21].CBDR.R = 0;
	SIU.PCR[69].R = 0x0600;
	
	/* PE6 */
	EMIOS_0.CH[22].CCR.B.BSL = 0x0;
	EMIOS_0.CH[22].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[22].CCR.B.EDPOL = 1;
	EMIOS_0.CH[22].CADR.R = 0;
	EMIOS_0.CH[22].CBDR.R = 0;
	SIU.PCR[70].R = 0x0600;
#if 0
	/* �Ҳ���BUG�������ò��ˣ������ǵ�Ƭ���ͺŲ�ͬ */
	/* PD13 */
	EMIOS_0.CH[25].CCR.B.BSL = 0x0;
	EMIOS_0.CH[25].CCR.B.MODE = 0x60;
 	EMIOS_0.CH[25].CCR.B.EDPOL = 1;
	EMIOS_0.CH[25].CADR.R = 0;
	EMIOS_0.CH[25].CBDR.R = 0;
	SIU.PSMI[26].R = 0;
	SIU.PCR[61].R = 0x0A00;
#endif
}