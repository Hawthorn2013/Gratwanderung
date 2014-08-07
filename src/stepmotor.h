#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__

#define ZUNAMHE_DRAWBRIDGE_UP (50)	/* µı«≈…˝∆æ‡¿Î */
#define ZUNAMHE_DRAHTBRIDGE_DOWN (50)	/* ∏÷Àø«≈µ¯¬‰æ‡¿Î */

#define STEPMOTOR_DIR (SIU.GPDO[3].R)

extern void init_EMIOS_0_StepMotor(void);
extern void open_StepMotor(int dir);
extern void close_StepMotor(void);
extern void init_StepMotor_counter(void);
extern void set_StepMotor(SDWORD site);


/* StepMotor data */
#ifdef __STEPMOTOR_C_
struct
{
	SDWORD current_site;
	SDWORD target_site;
	int current_dir;
	int target_dir;
	int is_OK;
} data_StepMotor = { 0, 0, 0, 0, 0 };
#else
extern struct
{
	SDWORD current_site;
	SDWORD target_site;
	int current_dir;
	int target_dir;
	int is_OK;
} data_StepMotor;
#endif


#endif