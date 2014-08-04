#define __STEPMOTOR_C_
#include "includes.h"


void INTC_StepMotor_Counter_Matched(void);

/*-----------------------------------------------------------------------*/
/* ��ʼ���������                                                        */
/*-----------------------------------------------------------------------*/
void init_EMIOS_0_StepMotor(void)
{
	/* eMIOS0��ʼ��80MHz��Ϊ10MHz */
	EMIOS_0.MCR.B.GPRE= 7;	/* GPRE+1=��Ƶϵ����/* Divide 80 MHz sysclk by 7+1 = 8 for 10MHz eMIOS clk */
	EMIOS_0.MCR.B.GPREN = 1;	/* Enable eMIOS clock */
	EMIOS_0.MCR.B.GTBE = 1;   /* Enable global time base */
	EMIOS_0.MCR.B.FRZ = 1;    /* Enable stopping channels when in debug mode */

    /* Modulus Up Counter 50HZ */
    EMIOS_0.CH[8].CCR.B.UCPRE=0;	/* Set channel prescaler to divide by 4 */
	EMIOS_0.CH[8].CCR.B.UCPEN = 1;	/* Enable prescaler; uses default divide by 4 */
	EMIOS_0.CH[8].CCR.B.FREN = 1;	/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[8].CADR.R = 2500;	/* ��������0.02s  50HZ */
	EMIOS_0.CH[8].CCR.B.MODE = 0x50;	/* Modulus Counter Buffered (MCB) */
	EMIOS_0.CH[8].CCR.B.BSL = 0x3;	/* Use internal counter */
    /* ������ PWM PA9 ���0-50000 */
	EMIOS_0.CH[9].CCR.B.BSL = 0x1;	/* Use counter bus C (default) */
	EMIOS_0.CH[9].CCR.B.MODE = 0x00;	/* ����� */  
    EMIOS_0.CH[9].CCR.B.EDPOL = 1;	/* Polarity-leading edge sets output/trailing clears*/
	EMIOS_0.CH[9].CADR.R = 1;	/* Leading edge when channel counter bus=250*/
	EMIOS_0.CH[9].CBDR.R = 1000;	/* Trailing edge when channel counter bus=500*/
	SIU.PCR[9].R = 0x0600;	/* [11:10]ѡ��AFx �˴�AF1 /* MPC56xxS: Assign EMIOS_0 ch 21 to pad */
	
	SIU.PCR[3].R = 0x0203;	/* PA3 */
	STEPMOTOR_DIR = 0;
	
	data_StepMotor.is_OK = 1;
}


/*-----------------------------------------------------------------------*/
/* �򿪲������                                                          */
/*-----------------------------------------------------------------------*/
void open_StepMotor(int dir)
{
	EMIOS_0.CH[9].CCR.B.MODE = 0x60;	/* Mode is OPWM Buffered */
	
	STEPMOTOR_DIR = (BYTE)dir;
}


/*-----------------------------------------------------------------------*/
/* �رղ������                                                          */
/*-----------------------------------------------------------------------*/
void close_StepMotor(void)
{
	EMIOS_0.CH[9].CCR.B.MODE = 0x00;	/* Mode is OPWM Buffered */
}


/*-----------------------------------------------------------------------*/
/* ����ģ��                                                              */
/*-----------------------------------------------------------------------*/
void init_StepMotor_counter(void)	//PD12ģ����������ڣ�������
{
	/* �������� PD12 */
	EMIOS_0.CH[24].CCR.B.MODE = 0x11;	//0x51;	//	/* Mode is MCB */
	EMIOS_0.CH[24].CCR.B.BSL = 0x3;	/* Use internal counter */
	EMIOS_0.CH[24].CCR.B.UCPRE=0;	/* Set channel prescaler to divide by 1 */
	EMIOS_0.CH[24].CCR.B.UCPEN = 1;	/* Enable prescaler; uses default divide by 1 */
	EMIOS_0.CH[24].CCR.B.FREN = 0;	/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[24].CCR.B.EDPOL=1;	/* Edge Select rising edge */
	EMIOS_0.CH[24].CADR.R = 0xffff;
	EMIOS_0.CH[24].CCR.B.FEN = 1;
	/* (WORD)EMIOS_0.CH[24].CCNTR.R ���ݼĴ��� */
	
	INTC_InstallINTCInterruptHandler(INTC_StepMotor_Counter_Matched, 153, 3);
	SIU.PCR[60].R = 0x0100;	/* Initialize pad for eMIOS channel Initialize pad for input */
}


/*-----------------------------------------------------------------------*/
/* ��������ﵽԤ��ת��                                                  */
/*-----------------------------------------------------------------------*/
void INTC_StepMotor_Counter_Matched(void)
{
	close_StepMotor();
	data_StepMotor.is_OK = 1;
	
	EMIOS_0.CH[24].CSR.B.FLAG = 1;
}


/*-----------------------------------------------------------------------*/
/* ���Ʋ������                                                          */
/*-----------------------------------------------------------------------*/
void set_StepMotor(SDWORD siteZunamhe)
{
#if 0
	data_StepMotor.is_OK = 0;
	data_StepMotor.target_site = site;
	if (data_StepMotor.current_site > data_StepMotor.target_site)
	{
		data_StepMotor.target_dir = 1;
	}
	else
	{
		data_StepMotor.target_dir = 0;
	}
#endif
	if (!siteZunamhe)
	{
		return;
	}
	data_StepMotor.is_OK = 0;
	data_StepMotor.target_site = data_StepMotor.current_site + siteZunamhe;
	if (data_StepMotor.current_site > data_StepMotor.target_site)
	{
		data_StepMotor.target_dir = 1;
	}
	else
	{
		data_StepMotor.target_dir = 0;
	}
	EMIOS_0.CH[24].CCR.B.MODE = 0x00;
	EMIOS_0.CH[24].CCR.B.MODE = 0x11;
	if (siteZunamhe > 0)
	{
		EMIOS_0.CH[24].CADR.R = siteZunamhe;
		open_StepMotor(0);
	}
	else
	{
		EMIOS_0.CH[24].CADR.R = 0 - siteZunamhe;
		open_StepMotor(1);
	}
}