#ifndef __HEHEACTION_H__
#define __HEHEACTION_H__

#define MAX (2500)
#define MIN (0)

/* µÆ19¿ÚÊý¾Ý */
#ifdef __HEHEACTION_C_
struct
{
	vuint32_t *light;
	BYTE bright;
}HHL[9]={0};
#else
extern struct
{
	vuint32_t *light;
	BYTE bright;
}HHL[9];
#endif

extern int g_f_D_start;
extern int g_f_G_start;
extern int g_f_X_start;
extern int g_f_G_double;
 
void init_HHL(void);
void ALL_HEHE_FLASHMOB(void);
void WIFI_D_action(WORD cmd);
void WIFI_G_action(WORD cmd);
void WIFI_X_action(WORD cmd);
void all_action_control(void);


#endif