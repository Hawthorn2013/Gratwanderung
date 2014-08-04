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
	init_key();
	init_test_LED();
	enable_irq();
	
	initLCD();
	LCD_DISPLAY();
	LCD_Fill(0x00);
	
	/* Loop forever */
	for (;;)
	{
#if 0
		/* ÷¥––‘∂≥Ã√¸¡Ó */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}
#endif

#if 1
		if (!K1)
		{
			D0 = 0;
		}
		if (!K2)
		{
			D0 = 1;
		}
		if (!K3)
		{
			D1 = 0;
		}
		if (!K4)
		{
			D1 = 1;
		}
		if (!K5)
		{
			D2 = ~D2;
		}
#endif
		delay_ms(100);
	}
}


