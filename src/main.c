#include "includes.h"

int main(void)
{
	int i = 0,j = 0;
	
	disable_watchdog();
	init_modes_and_clock();
	init_pit();
	init_led();
	init_hehelight();
	init_EMIOS_0_StepMotor();
	init_StepMotor_counter();
	init_serial_port_0();
	init_serial_port_1();
	//init_serial_port_2();
	//init_serial_port_3();
	//init_optical_encoder();
	init_DSPI_1();
	init_device_select_IO();
	init_key();
	//init_test_LED();
	enable_irq();
	
	
#if 1	
	/* 设备选择 */
	if (0 == DEVICE_SELECT_IO)
	{
		g_device_NO = WIFI_ADDRESS_DRAWBRIDGE;	/* 吊桥 */
	}
	else
	{
		g_device_NO = WIFI_ADDRESS_DRAHTBRIDGE;	/* 钢丝桥 */
	}
#endif	
	initLCD();
	LCD_DISPLAY();
	LCD_Fill(0x00);
	
	/* Loop forever */
	for (;;)
	{
#if 1
		/* 执行远程命令 */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}
#endif

#if 1
		/* 执行赛场网络控制命令 */
		if (1 == g_net_control_data.is_new_cmd)
		{
			g_net_control_data.is_new_cmd = 0;
			
			execute_net_cmd(g_net_control_data.cmd);
		}
#endif
		/*通知2、4启动*/
		if(g_f_fly_bridge==1 && g_f_fly_bridge_wifi==1)
		{
			for(j=0;j<5;j++)
				send_net_cmd(WIFI_ADDRESS_CAR_2,WIFI_CMD_NET_BRIDGE);
			for(j=0;j<5;j++)
				send_net_cmd(WIFI_ADDRESS_CAR_4,WIFI_CMD_NET_BRIDGE);
			g_f_fly_bridge = 0;
			g_f_fly_bridge_wifi=0;
		}
#if 1
		/* 桥测试 */
		if (!K2)
		{
			if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
			}
			else if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
			}
		}
		/*桥回位*/
		if (!K3)
		{
			if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
			{
				set_StepMotor((SDWORD)ZUNAMHE_DRAWBRIDGE_UP);
				g_f_drawbridge=0;
			}
			else if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
			{
				set_StepMotor((SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN);
				g_f_drahtbridge=0;
			}
		}
		/*K4 桥正微调*/
		if (!K4)
		{
			if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAWBRIDGE_UP_TEST);
			}
			else if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
			{
				set_StepMotor(0-(SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN_TEST);
			}
		}
		/*K5桥负微调*/
		if (!K5)
		{
			if (WIFI_ADDRESS_DRAWBRIDGE == g_device_NO)
			{
				set_StepMotor((SDWORD)ZUNAMHE_DRAWBRIDGE_UP_TEST);
			}
			else if (WIFI_ADDRESS_DRAHTBRIDGE == g_device_NO)
			{
				set_StepMotor((SDWORD)ZUNAMHE_DRAHTBRIDGE_DOWN_TEST);
			}
		}
#endif
		
		//hehelighton();
		
		//delay_ms(50);
		
		//hehelightoff();
		
		//delay_ms(50);
	}
}


