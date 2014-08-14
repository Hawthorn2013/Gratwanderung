/*  看什么看！赛道灯而已！  */

#ifndef __HEHELIGHT_H__
#define __HEHELIGHT_H__


#define HHL_PWM_MAX (2500)
#define HHL_PWM_MIN (0)



/* 0灭-2500最亮 */
#define HHL_PWM_1 (EMIOS_0.CH[1].CBDR.R)
#define HHL_PWM_2 (EMIOS_0.CH[2].CBDR.R)
#define HHL_PWM_3 (EMIOS_0.CH[3].CBDR.R)
#define HHL_PWM_4 (EMIOS_0.CH[4].CBDR.R)
#define HHL_PWM_5 (EMIOS_0.CH[5].CBDR.R)
#define HHL_PWM_6 (EMIOS_0.CH[6].CBDR.R)
#define HHL_PWM_7 (EMIOS_0.CH[7].CBDR.R)
/* 无8-9 */
#define HHL_PWM_10 (EMIOS_0.CH[10].CBDR.R)
#define HHL_PWM_11 (EMIOS_0.CH[11].CBDR.R)
#define HHL_PWM_12 (EMIOS_0.CH[12].CBDR.R)
#define HHL_PWM_13 (EMIOS_0.CH[13].CBDR.R)
#define HHL_PWM_14 (EMIOS_0.CH[14].CBDR.R)
#define HHL_PWM_15 (EMIOS_0.CH[15].CBDR.R)
#define HHL_PWM_16 (EMIOS_0.CH[16].CBDR.R)
#define HHL_PWM_17 (EMIOS_0.CH[17].CBDR.R)
#define HHL_PWM_18 (EMIOS_0.CH[18].CBDR.R)
/* 无19 */
#define HHL_PWM_20 (EMIOS_0.CH[20].CBDR.R)
#define HHL_PWM_21 (EMIOS_0.CH[21].CBDR.R)
#define HHL_PWM_22 (EMIOS_0.CH[22].CBDR.R)

#define HHL_1_1 HHL_PWM_1
#define HHL_1_2 HHL_PWM_2
#define HHL_1_3 HHL_PWM_3
#define HHL_1_4 HHL_PWM_4
#define HHL_1_5 HHL_PWM_5
#define HHL_1_6 HHL_PWM_6
#define HHL_1_7 HHL_PWM_7
#define HHL_2_1 HHL_PWM_10
#define HHL_2_2 HHL_PWM_11
#define HHL_2_3 HHL_PWM_12
#define HHL_2_4 HHL_PWM_13
#define HHL_2_5 HHL_PWM_14
#define HHL_2_6 HHL_PWM_15
#define HHL_2_7 HHL_PWM_16
#define HHL_3_1 HHL_PWM_17
#define HHL_3_2 HHL_PWM_18
#define HHL_3_3 HHL_PWM_20
#define HHL_3_4 HHL_PWM_21
#define HHL_3_5 HHL_PWM_22
/* 无3_6-3_7 */

/* 呵呵灯控制数据 */
typedef struct
{
	vuint32_t *pLightness;	/* 指向PWM占空比寄存器的指针 */
	BYTE enable;	/* 使能位 */
	WORD zunahme;	/* 每次进入PIT中断PWM占空比寄存器增量，越大灯变化越快 */
	BYTE is_increasing;	/* 亮度正在增加标志位 */
	BYTE g_f_close;		/*渐灭标志位*/
}HHL_Light_Data;

extern HHL_Light_Data (HHL_light_datas[4][8]);

extern void init_hehelight_PWM(void);
extern void contorl_HHLs(void);
extern void set_HHL_mode(HHL_Light_Data* hhl, WORD zunahme, BYTE is_increasing, DWORD original_lightness);
extern void close_HHL(HHL_Light_Data* hhl);



#endif