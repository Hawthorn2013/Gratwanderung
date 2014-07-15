#ifndef __INIT_H__
#define __INIT_H__


#define PERIPH_SET_1_CLK_16M
#define STEER_HELM_DATA (EMIOS_0.CH[9].CBDR.R)

#define KEY1 (SIU.GPDI[48].B.PDI)
#define KEY2 (SIU.GPDI[50].B.PDI)
#define KEY3 (SIU.GPDI[52].B.PDI)
#define KEY4 (SIU.GPDI[54].B.PDI)
#define KEY5 (SIU.GPDI[56].B.PDI)


extern void init_modes_and_clock(void);
extern void disable_watchdog(void);
extern void initEMIOS_0MotorAndSteer(void);
extern void init_led(void);
extern void init_pit(void);
extern void init_encoder(void);
extern void enable_irq(void);
extern int is_big_endian();




extern void init_optical_encoder(void);
void delay_us(DWORD us);
void delay_ms(DWORD ms);


#endif