#define __HEHEACTION_C_
#include "includes.h"

int g_f_D_start=0;
int g_f_G_start=0;
int g_f_X_start=0;
int g_f_G_double=0;

void ALL_HEHE_FLASHMOB(void)	/*��������*/
{
	int i=0;
	for(i=0;i<3;i++)
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
}

void WIFI_D_action(WORD cmd)
{
	if(WIFI_CMD_NET_3_1==cmd)
	{
		set_HHL_mode(&(HHL_light_datas[1][1]),30,TRUE,HHL_PWM_MIN);
	}
	if(WIFI_CMD_NET_3_2==cmd)
	{
		
		if(g_f_drawbridge==0)	/*��ʼ����*/
		{
			close_HHL(&(HHL_light_datas[1][1]));
			HHL_1_1=2500;	//ȫ��
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
			g_f_drawbridge=1;
			g_f_fly_bridge_wifi=1;	
			delay_ms(800);	/*�ȴ�������*/
			HHL_1_1=1500;	//����
		}
	}
	
}

void WIFI_G_action(WORD cmd)
{
	if(WIFI_CMD_NET_5_1==cmd)
	{
		set_HHL_mode(&(HHL_light_datas[3][1]),30,TRUE,HHL_PWM_MIN);		/*��˿�ź���*/	
	}
	if(WIFI_CMD_NET_6_3==cmd)
	{
		if(g_f_drahtbridge==0)	/*��˿�ŵ���*/
		{
			close_HHL(&(HHL_light_datas[3][1]));	/*������ֹͣ*/
			
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
			g_f_drahtbridge=1;
			
			delay_ms(500);	/*�ȴ��ŵ���*/
			HHL_3_2=2500;	/*��˿����*/
		}
	}
	if(WIFI_CMD_NET_6_3_2==cmd)	/*�߸�˿����*/
	{
		set_HHL_mode(&(HHL_light_datas[3][1]),10,TRUE,HHL_PWM_MIN);
		HHL_3_2=1500;	/*��˿����*/
	}
}

void WIFI_X_action(WORD cmd)
{
	if(WIFI_CMD_NET_5_1==cmd)
	{
		delay_ms(300);
		set_HHL_mode(&(HHL_light_datas[2][1]),30,TRUE,HHL_PWM_MIN);
	}
}

void all_action_control(void)
{
	if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
	{
		if (g_net_control_data.is_new_cmd)
		{
			g_net_control_data.is_new_cmd = 0;	
			WIFI_D_action(g_net_control_data.cmd);
			WIFI_X_action(g_net_control_data.cmd);
		}
	}
	if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
	{
		if (g_net_control_data.is_new_cmd)
		{
			g_net_control_data.is_new_cmd = 0;	
			WIFI_G_action(g_net_control_data.cmd);
		}
	}
}