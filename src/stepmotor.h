#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__

#define ZUNAMHE_DRAWBRIDGE_UP (5000)	/* µı«≈…˝∆æ‡¿Î */
#define ZUNAMHE_DRAWBRIDGE_UP_TEST (200)   //≤‚ ‘≤π÷µ
#define ZUNAMHE_DRAHTBRIDGE_DOWN (4800)	/* ∏÷Àø«≈µ¯¬‰æ‡¿Î */
#define ZUNAMHE_DRAHTBRIDGE_DOWN_TEST (200)   //≤‚ ‘≤π÷µ


#define STEPMOTOR_DIR (SIU.GPDO[3].R)

extern void init_EMIOS_0_StepMotor(void);
extern void open_StepMotor(int dir);
extern void close_StepMotor(void);
extern void init_StepMotor_counter(void);
extern void set_StepMotor(SDWORD siteZunamhe);

extern int g_f_fly_bridge;

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