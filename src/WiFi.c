#define __WIFI_C_
#include "includes.h"

int g_f_drawbridge=0;
int g_f_drahtbridge=0;

int g_f_fly_bridge_wifi=0;
int g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
int g_remote_frame_cnt = 0;
BYTE remote_frame_data[REMOTE_FRAME_LENGTH];
BYTE remote_frame_data_send[REMOTE_FRAME_LENGTH];
BYTE g_device_NO = WIFI_ADDRESS_DRAWBRIDGE;	/* 设备号 即WiFi地址 */


/*-----------------------------------------------------------------------*/
/* 执行远程命令                                                                      */
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
/* 接受远程数据帧                                                        */
/*-----------------------------------------------------------------------*/
int rev_remote_frame(BYTE rev)
{
	if (g_remote_frame_cnt == 0)	//接收帧头
	{
		if (rev == 0xAA)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xAA;
		}
	}
	else if (g_remote_frame_cnt == 1)	//接收帧头
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
	else if (g_remote_frame_cnt == 2)	//接收地址
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt == 3)	//接收地址
	{
		WORD address = 0x0000;
		
		remote_frame_data[g_remote_frame_cnt++] = rev;
		address |= (WORD)(remote_frame_data[2])<<8;
		address |= (WORD)(remote_frame_data[3]);
		if (address != ((WORD)0x0001<<g_device_NO))
		{
			g_remote_frame_cnt = 0;	//不是发给本机的
		}
	}
	else if (g_remote_frame_cnt == 4)	//接收长度
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev+6>REMOTE_FRAME_LENGTH)	//判断是否会导致缓冲区溢出
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt>4 && g_remote_frame_cnt<=remote_frame_data[4]+4)	//接收数据区
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt==remote_frame_data[4]+4+1)	//接收校验字节	
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
/* 接受远程数据帧                                                        */
/* 第二版                                                                */
/* 修改地址位定义:源地址(1B)+目的地址(1B)                                */
/* AA BB 源地址(1B) 目的地址(1B) 长度(1B) 数据体 校验字(1B)              */
/* 未改变原数据帧的大部分定义及长度                                      */
/*-----------------------------------------------------------------------*/
int rev_remote_frame_2(BYTE rev)
{
	if (g_remote_frame_cnt == 0)	//接收帧头
	{
		if (rev == 0xAA)
		{
			remote_frame_data[g_remote_frame_cnt++] = 0xAA;
		}
	}
	else if (g_remote_frame_cnt == 1)	//接收帧头
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
	else if (g_remote_frame_cnt == 2)	//接收源地址
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt == 3)	//接收目的地址
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev != g_device_NO)
		{
			g_remote_frame_cnt = 0;	//不是发给本机的
		}
	}
	else if (g_remote_frame_cnt == 4)	//接收长度
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
		if (rev+6>REMOTE_FRAME_LENGTH)	//判断是否会导致缓冲区溢出
		{
			g_remote_frame_cnt = 0;
		}
	}
	else if (g_remote_frame_cnt>4 && g_remote_frame_cnt<=remote_frame_data[4]+4)	//接收数据区
	{
		remote_frame_data[g_remote_frame_cnt++] = rev;
	}
	else if (g_remote_frame_cnt==remote_frame_data[4]+4+1)	//接收校验字节	
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
/* 生成并发送远程命令                                                    */
/* 参数 : cmd WiFi命令字                                                 */
/*        data发出的数据体，接在cmd后                                    */
/*        data长度                                                       */
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
	for (; i < REMOTE_FRAME_LENGTH; i++)	/* 清空未使用区域 */
	{
		remote_frame_data_send[i] = 0x00;
	}
	serial_port_0_TX_array(remote_frame_data_send, REMOTE_FRAME_LENGTH);
}


/*-----------------------------------------------------------------------*/
/* 生成并发送远程命令                                                    */
/* 第二版                                                                */
/* 修改地址位定义:源地址(1B)+目的地址(1B)                                */
/* AA BB 源地址(1B) 目的地址(1B) 长度(1B) 数据体 校验字(1B)              */
/* 未改变原数据帧的大部分定义及长度                                      */
/* 参数 : scr 源地址                                                     */
/*        des 目标地址                                                   */
/*        cmd WiFi命令字                                                 */
/*        length data长度                                                */
/*        data发出的数据体，接在cmd后                                    */
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
	for (; i < REMOTE_FRAME_LENGTH; i++)	/* 清空未使用区域 */
	{
		remote_frame_data_send[i] = 0x00;
	}
	serial_port_0_TX_array(remote_frame_data_send, REMOTE_FRAME_LENGTH);
}


/*-----------------------------------------------------------------------*/
/* 发送赛场网络控制命令                                                          */
/* 依赖generate_remote_frame_2()                                           */
/*-----------------------------------------------------------------------*/
void send_net_cmd(BYTE des, WORD net_cmd)
{
	generate_remote_frame_2(g_device_NO, des, WIFI_CMD_NET, sizeof(net_cmd), (const BYTE *)(&net_cmd));
}


#if 0
/*-----------------------------------------------------------------------*/
/* 执行赛场网络控制                                                                */
/*-----------------------------------------------------------------------*/
void execute_net_cmd(WORD cmd)
{
	switch (cmd)
	{
		case WIFI_CMD_NET_3_2 :	/* 吊桥升起 */
		if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
		{
			if(g_f_drawbridge==0)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
				g_f_drawbridge=1;
				g_f_fly_bridge_wifi=1;	
			}
		}
		break;
		
		case WIFI_CMD_NET_6_3 :	/* 钢丝桥塌陷 */
		if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
		{
			if(g_f_drahtbridge==0)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
				g_f_drahtbridge=1;
			}
		}
		break;
		
	}
}
#endif


/*-----------------------------------------------------------------------*/
/* 异或校验                                                                            */
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