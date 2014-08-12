#include "includes.h"


int main(void)
{
	int i = 0;
	
	disable_watchdog();
	init_modes_and_clock();
	init_pit();
	init_led();
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
	/* �豸ѡ�� */
	if (0 == DEVICE_SELECT_IO)
	{
		g_device_NO = WIFI_ADDRESS_DRAWBRIDGE;	/* ���� */
	}
	else
	{
		g_device_NO = WIFI_ADDRESS_DRAHTBRIDGE;	/* ��˿�� */
	}
#endif	
	initLCD();
	LCD_DISPLAY();
	LCD_Fill(0x00);
	
	/* Loop forever */
	for (;;)
	{
#if 1
		/* ִ��Զ������ */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}
#endif

#if 1
		/* ִ����������������� */
		if (1 == g_net_control_data.is_new_cmd)
		{
			g_net_control_data.is_new_cmd = 0;
			
			execute_net_cmd(g_net_control_data.cmd);
		}
#endif

#if 1
		/* �Ų��� */
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
		/*�Ż�λ*/
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
		/*K4 ����΢��*/
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
		/*K5�Ÿ�΢��*/
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
		delay_ms(100);
	}
}


