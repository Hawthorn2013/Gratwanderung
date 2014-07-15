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
	enable_irq();
	
	initLCD();
	LCD_DISPLAY();
	LCD_Fill(0x00);

	/* Loop forever */
	for (;;)
	{
#if 1
		/* ÷¥––‘∂≥Ã√¸¡Ó */
		if (REMOTE_FRAME_STATE_OK == g_remote_frame_state)
		{
			g_remote_frame_state = REMOTE_FRAME_STATE_NOK;
			
			execute_remote_cmd(remote_frame_data+5);
		}
#endif
		
		delay_ms(100);
	}
}


