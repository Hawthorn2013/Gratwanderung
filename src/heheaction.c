#define __HEHEACTION_C_
#include "includes.h"

int g_f_D_start=0;
int g_f_G_start=0;
int g_f_X_start=0;
int g_f_G_double=0;

void ALL_HEHE_FLASHMOB(void)	/*��������*/
{
	int i,j=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			set_HHL_mode(&(HHL_light_datas[i][j]),60,TRUE,HHL_PWM_MIN);
		}
	}
	delay_ms(3000);
	for (i = 0; i < 4 * 8; i++)
	{
		((HHL_Light_Data *)HHL_light_datas)[i].enable = FALSE;
	}
}

void WIFI_D_action(WORD cmd)
{
	if(WIFI_CMD_NET_3_1==cmd)		/*��Ҫ�ϵ���*/
	{
		set_HHL_mode(&(HHL_light_datas[1][1]),30,TRUE,HHL_PWM_MIN);
	}
	if(WIFI_CMD_NET_3_2==cmd)
	{
		if(g_f_drawbridge==0)	/*��ʼ����*/
		{
			close_HHL(&(HHL_light_datas[1][1]));
			set_HHL_mode(&(HHL_light_datas[1][2]),0,TRUE,500);	//����Ű���
			set_HHL_mode(&(HHL_light_datas[1][1]),60,TRUE,HHL_PWM_MIN);	//ǰ���ź�������
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
			g_f_drawbridge=1;
			//g_f_fly_bridge_wifi=1;	
			delay_ms(1500);	/*�ȴ�������*/
			close_HHL(&(HHL_light_datas[1][1]));
			set_HHL_mode(&(HHL_light_datas[1][1]),30,TRUE,HHL_PWM_MIN);	//ǰ���ź�������
		}
	}
	if(WIFI_CMD_NET_5_1_2==cmd)	/*2�ų�����뿪����*/
	{
		set_HHL_mode(&(HHL_light_datas[1][1]),0,TRUE,200);
		set_HHL_mode(&(HHL_light_datas[1][2]),0,TRUE,200);
	}
}

void WIFI_G_action(WORD cmd)
{
	if(WIFI_ADDRESS_DRAHTBRIDGE==g_device_NO)
	{
		if(WIFI_CMD_NET_6_3==cmd)
		{
			if(g_f_drahtbridge==0)	/*��˿�ŵ���*/
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
				g_f_drahtbridge=1;
				send_net_cmd(WIFI_ADDRESS_DRAWBRIDGE,WIFI_CMD_NET_6_3_3);
			}
		}
	}
	if(WIFI_ADDRESS_DRAWBRIDGE==g_device_NO)
	{
		if(WIFI_CMD_NET_5_1_3==cmd)	/*4�ų���������*/
		{
			set_HHL_mode(&(HHL_light_datas[3][1]),30,TRUE,HHL_PWM_MIN);		/*��˿�ź���*/	
		}
		if(WIFI_CMD_NET_6_3_3==cmd)	/*��˿�ŵ���*/
		{
			//close_HHL(&(HHL_light_datas[3][1]));	/*������ֹͣ*/
			delay_ms(1000);	/*�ȴ��ŵ���*/
			set_HHL_mode(&(HHL_light_datas[3][1]),60,TRUE,HHL_PWM_MIN);	/*��˿��������*/
		}
		if(WIFI_CMD_NET_6_3_2==cmd)	/*�߸�˿����*/
		{
			delay_ms(500);
			set_HHL_mode(&(HHL_light_datas[3][1]),0,TRUE,200);
			
		}
	}
	

	
}

void WIFI_X_action(WORD cmd)
{
	if(WIFI_CMD_NET_5_1==cmd)
	{
		delay_ms(300);
		set_HHL_mode(&(HHL_light_datas[2][1]),30,TRUE,HHL_PWM_MIN);
	}
	if(WIFI_CMD_NET_5_2==cmd)
	{
		close_HHL(&(HHL_light_datas[2][1]));
		set_HHL_mode(&(HHL_light_datas[2][1]),0,TRUE,200);
	}
}

void WIFI_W_action(WORD cmd)
{
	int i=0;
	if(WIFI_CMD_NET_4_1==cmd)
	{
		for(i=3;i<8;i++)
		{
			set_HHL_mode(&(HHL_light_datas[2][i]),30,TRUE,HHL_PWM_MIN);
		}
	}
	if(WIFI_CMD_NET_4_2==cmd)
	{
		for(i=3;i<8;i++)
		{
			close_HHL(&(HHL_light_datas[2][i]));
			enable_HHL_flow(&(HHL_flow_datas[i-3]));
		}
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
			WIFI_G_action(g_net_control_data.cmd);
		}
	}
	if(WIFI_ADDRESS_DRAHTBRIDGE==g_device_NO)
	{
		if (g_net_control_data.is_new_cmd)
		{
			WIFI_G_action(g_net_control_data.cmd);
		}
	}
}