#define __WIFI_C_
#include "includes.h"


int g_f_fly_bridge_wifi=0;
int g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
int g_remote_frame_cnt = 0;
BYTE remote_frame_data[REMOTE_FRAME_LENGTH];
BYTE remote_frame_data_send[REMOTE_FRAME_LENGTH];
BYTE g_device_NO = WIFI_ADDRESS_DRAWBRIDGE;	/* �豸�� ��WiFi��ַ */


/*-----------------------------------------------------------------------*/
/* ִ��Զ������                                                                      */
/*-----------------------------------------------------------------------*/
void execute_remote_cmd(const BYTE *data)
{
	WORD cmd = 0;
	
	cmd = ((WORD)(data[0])<<8) | ((WORD)(data[1]));
	switch (cmd)
	{
		case WIFI_CMD_NET :
		g_net_control_data.is_new_cmd = 1;
		g_net_control_data.cmd = *((WORD *)(&(data[2])));
		break;
	}
}


/*-----------------------------------------------------------------------*/
/* ����Զ������֡                                                        */
/*-----------------------------------------------------------------------*/
int rev_remote_frame(BYTE rev)
{
	if (g_remote_frame_cnt == 0)	//����֡ͷ
	{
		if (rev == 0xAA)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xAA;
		}
	}
	else if (g_remote_frame_cnt == 1)	//����֡ͷ
	{
		if (rev == 0xBB)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xBB;
		}
		else
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt == 2)	//���յ�ַ
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt == 3)	//���յ�ַ
	{
		WORD address = 0x0000;
		
		remote_frame_data[g_remote_frame_cnt++] = rev;
		address |= (WORD)(remote_frame_data[2])<<8;
		address |= (WORD)(remote_frame_data[3]);
		if (address != ((WORD)0x0001<<g_device_NO))
		{
			g_remote_frame_cnt = 0;	//���Ƿ���������
		}
	}
	else if (g_remote_frame_cnt == 4)	//���ճ���
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev+6>REMOTE_FRAME_LENGTH)	//�ж��Ƿ�ᵼ�»��������
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt>4 && g_remote_frame_cnt<=remote_frame_data[4]+4)	//����������
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt==remote_frame_data[4]+4+1)	//����У���ֽ�	
	{
		BYTE sum;
		
		remote_frame_data[g_remote_frame_cnt++] = rev;
		sum = check_sum((const BYTE *)(remote_frame_data+2), (WORD)(remote_frame_data[4]+3));
		if (sum != remote_frame_data[remote_frame_data[4]+5])
		{
			g_remote_frame_cnt = 0;	//CheckSum Fail
		}
		else
		{
			g_remote_frame_cnt = 0;
			g_remote_frame_state = REMOTE_FRAME_STATE_OK;	//CheckSum Success
		}
	}
	
	return g_remote_frame_state;
}


/*-----------------------------------------------------------------------*/
/* ����Զ������֡                                                        */
/* �ڶ���                                                                */
/* �޸ĵ�ַλ����:Դ��ַ(1B)+Ŀ�ĵ�ַ(1B)                                */
/* AA BB Դ��ַ(1B) Ŀ�ĵ�ַ(1B) ����(1B) ������ У����(1B)              */
/* δ�ı�ԭ����֡�Ĵ󲿷ֶ��弰����                                      */
/*-----------------------------------------------------------------------*/
int rev_remote_frame_2(BYTE rev)
{
	if (g_remote_frame_cnt == 0)	//����֡ͷ
	{
		if (rev == 0xAA)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xAA;
		}
	}
	else if (g_remote_frame_cnt == 1)	//����֡ͷ
	{
		if (rev == 0xBB)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xBB;
		}
		else
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt == 2)	//����Դ��ַ
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt == 3)	//����Ŀ�ĵ�ַ
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev != g_device_NO)
		{
			g_remote_frame_cnt = 0;	//���Ƿ���������
		}
	}
	else if (g_remote_frame_cnt == 4)	//���ճ���
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev+6>REMOTE_FRAME_LENGTH)	//�ж��Ƿ�ᵼ�»��������
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt>4 && g_remote_frame_cnt<=remote_frame_data[4]+4)	//����������
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt==remote_frame_data[4]+4+1)	//����У���ֽ�	
	{
		BYTE sum;
		
		remote_frame_data[g_remote_frame_cnt++] = rev;
		sum = check_sum((const BYTE *)(remote_frame_data+2), (WORD)(remote_frame_data[4]+3));
		if (sum != remote_frame_data[remote_frame_data[4]+5])
		{
			g_remote_frame_cnt = 0;	//CheckSum Fail
		}
		else
		{
			g_remote_frame_cnt = 0;
			g_remote_frame_state = REMOTE_FRAME_STATE_OK;	//CheckSum Success
		}
	}
	
	return g_remote_frame_state;
}


/*-----------------------------------------------------------------------*/
/* ���ɲ�����Զ������                                                    */
/* ���� : cmd WiFi������                                                 */
/*        data�����������壬����cmd��                                    */
/*        data����                                                       */
/*-----------------------------------------------------------------------*/
void generate_remote_frame(WORD cmd, const BYTE data[], BYTE length)
{
	WORD i = 0, j = 0;
	
	remote_frame_data_send[i++] = 0xAA;
	remote_frame_data_send[i++] = 0xBB;
	remote_frame_data_send[i++] = (BYTE)((0x0001<<ANDROID_ADDRESS)>>8);
	remote_frame_data_send[i++] = (BYTE)(0x0001<<ANDROID_ADDRESS);
	remote_frame_data_send[i++] = length+2;
	remote_frame_data_send[i++] = (BYTE)(cmd>>8);
	remote_frame_data_send[i++] = (BYTE)cmd;
	for (j = 0; j < length; j++)
	{
		remote_frame_data_send[i++] = data[j];
	}
	remote_frame_data_send[i++] = check_sum(remote_frame_data_send+2, i-3);
	for (; i < REMOTE_FRAME_LENGTH; i++)	/* ���δʹ������ */
	{
		remote_frame_data_send[i] = 0x00;
	}
	serial_port_0_TX_array(remote_frame_data_send, REMOTE_FRAME_LENGTH);
}


/*-----------------------------------------------------------------------*/
/* ���ɲ�����Զ������                                                    */
/* �ڶ���                                                                */
/* �޸ĵ�ַλ����:Դ��ַ(1B)+Ŀ�ĵ�ַ(1B)                                */
/* AA BB Դ��ַ(1B) Ŀ�ĵ�ַ(1B) ����(1B) ������ У����(1B)              */
/* δ�ı�ԭ����֡�Ĵ󲿷ֶ��弰����                                      */
/* ���� : scr Դ��ַ                                                     */
/*        des Ŀ���ַ                                                   */
/*        cmd WiFi������                                                 */
/*        length data����                                                */
/*        data�����������壬����cmd��                                    */
/*-----------------------------------------------------------------------*/
void generate_remote_frame_2(BYTE scr, BYTE des, WORD cmd, BYTE length, const BYTE data[])
{
	WORD i = 0, j = 0;
	
	remote_frame_data_send[i++] = 0xAA;
	remote_frame_data_send[i++] = 0xBB;
	remote_frame_data_send[i++] = scr;
	remote_frame_data_send[i++] = des;
	remote_frame_data_send[i++] = length+2;
	remote_frame_data_send[i++] = (BYTE)(cmd>>8);
	remote_frame_data_send[i++] = (BYTE)cmd;
	for (j = 0; j < length; j++)
	{
		remote_frame_data_send[i++] = data[j];
	}
	remote_frame_data_send[i++] = check_sum(remote_frame_data_send+2, i-2);
	for (; i < REMOTE_FRAME_LENGTH; i++)	/* ���δʹ������ */
	{
		remote_frame_data_send[i] = 0x00;
	}
	serial_port_0_TX_array(remote_frame_data_send, REMOTE_FRAME_LENGTH);
}


/*-----------------------------------------------------------------------*/
/* �������������������                                                          */
/* ����generate_remote_frame_2()                                           */
/*-----------------------------------------------------------------------*/
void send_net_cmd(BYTE des, WORD net_cmd)
{
	generate_remote_frame_2(g_device_NO, des, WIFI_CMD_NET, sizeof(net_cmd), (const BYTE *)(&net_cmd));
}


/*-----------------------------------------------------------------------*/
/* ִ�������������                                                                */
/*-----------------------------------------------------------------------*/
void execute_net_cmd(WORD cmd)
{
	switch (cmd)
	{
		case WIFI_CMD_NET_3_2 :	/* �������� */
		if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
		{
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
			g_f_fly_bridge_wifi=1;
		}
		break;
		case WIFI_CMD_NET_6_3 :	/* ��˿������ */
		if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
		{
			set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
		}
		break;
		
	}
}


/*-----------------------------------------------------------------------*/
/* ���У��                                                                            */
/*-----------------------------------------------------------------------*/
BYTE check_sum(const BYTE *data, WORD length)
{
	int i;
	BYTE res = 0;
	
	for (i=0; i<length; i++)
	{
		res ^= data[i];
	}
	
	return res;
}