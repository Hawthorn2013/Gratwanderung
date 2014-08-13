#define __HEHEACTION_C_
#include "includes.h"

int g_f_D_start=0;
int g_f_G_start=0;
int g_f_X_start=0;
int g_f_G_double=0;

void init_HHL(void)
{
	*(HHL[0].light)=HHL_1_1;
	*(HHL[1].light)=HHL_1_2;
	*(HHL[2].light)=HHL_1_3;
	*(HHL[3].light)=HHL_2_1;
	*(HHL[4].light)=HHL_2_2;
	*(HHL[5].light)=HHL_2_3;
	*(HHL[6].light)=HHL_3_1;
	*(HHL[7].light)=HHL_3_2;
	*(HHL[8].light)=HHL_3_3;
}

void ALL_HEHE_FLASHMOB(void)	/*¿ª³¡¿ìÉÁ*/
{
	HHL_1_1=MAX;
	HHL_1_2=MAX;
	HHL_1_3=MAX;
	HHL_2_1=MAX;
	HHL_2_2=MAX;
	HHL_2_3=MAX;
	HHL_3_1=MAX;
	HHL_3_2=MAX;
	HHL_3_3=MAX;
	delay_ms(800);
	HHL_1_1=MIN;
	HHL_1_2=MIN;
	HHL_1_3=MIN;
	HHL_2_1=MIN;
	HHL_2_2=MIN;
	HHL_2_3=MIN;
	HHL_3_1=MIN;
	HHL_3_2=MIN;
	HHL_3_3=MIN;
	delay_ms(800);
}

void WIFI_D_action(WORD cmd)
{
	if(WIFI_CMD_NET_3_1==cmd)
	{
		HHL[0].bright=1;
		g_f_D_start=1;		/*ºôÎüµÆ*/
	}
	if(WIFI_CMD_NET_3_2==cmd)
	{
		
		if(g_f_drawbridge==0)	/*¿ªÊ¼À­ÇÅ*/
		{
			g_f_D_start=0;
			HHL_1_1=2500;	//È«ÁÁ
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
			g_f_drawbridge=1;
			g_f_fly_bridge_wifi=1;	
			delay_ms(800);	/*µÈ´ýÇÅÉýÆð*/
			HHL_1_1=1500;	//°ëÁÁ
		}
	}
	
}

void WIFI_G_action(WORD cmd)
{
	if(WIFI_CMD_NET_5_1==cmd)
	{
		HHL[3].bright=1;
		g_f_G_start=1;		/*¸ÖË¿ÇÅºôÎü*/	
	}
	if(WIFI_CMD_NET_6_3==cmd)
	{
		if(g_f_drahtbridge==0)	/*¸ÖË¿ÇÅµøÂä*/
		{
			HHL_2_1=0;
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
			g_f_drahtbridge=1;
			g_f_G_start=0;
			
			delay_ms(500);	/*µÈ´ýÇÅµøÂä*/
			HHL_2_2=2500;	/*¸ÖË¿³¬ÁÁ*/
		}
	}
	if(WIFI_CMD_NET_6_3_2==cmd)	/*×ß¸ÖË¿½áÊø*/
	{
		HHL[3].bright=0;
		g_f_G_start=1;		/*¸ÖË¿ÇÅºôÎü*/
		HHL_2_2=1500;	/*¸ÖË¿°ëÁÁ*/
	}
}

void WIFI_X_action(WORD cmd)
{
	if(WIFI_CMD_NET_5_1==cmd)
	{
		delay_ms(300);
		g_f_X_start=1;		/*ºôÎüµÆ*/
	}
}