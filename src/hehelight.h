/*  看什么看！赛道灯而已！  */

#ifndef __HEHELIGHT_H__
#define __HEHELIGHT_H__


#define HHL_0 (SIU.GPDO[0].B.PDO)
#define HHL_1 (SIU.GPDO[1].B.PDO)
#define HHL_2 SIU.GPDO[2].B.PDO()
#define HHL_3 (SIU.GPDO[4].B.PDO)
#define HHL_4 (SIU.GPDO[5].B.PDO)
#define HHL_5 (SIU.GPDO[6].B.PDO)
#define HHL_6 (SIU.GPDO[7].B.PDO)
#define HHL_7 (SIU.GPDO[8].B.PDO)
#define HHL_8 (SIU.GPDO[10].B.PDO)
#define HHL_9 (SIU.GPDO[11].B.PDO)
#define HHL_10 (SIU.GPDO[16].B.PDO)
#define HHL_11 (SIU.GPDO[17].B.PDO)
#define HHL_12 (SIU.GPDO[26].B.PDO)
#define HHL_13 (SIU.GPDO[27].B.PDO)
#define HHL_14 (SIU.GPDO[28].B.PDO)
#define HHL_15 (SIU.GPDO[29].B.PDO)
#define HHL_16 (SIU.GPDO[30].B.PDO)
#define HHL_17 (SIU.GPDO[31].B.PDO)
#define HHL_18 (SIU.GPDO[32].B.PDO)
#define HHL_19 (SIU.GPDO[33].B.PDO)
#define HHL_20 (SIU.GPDO[35].B.PDO)

#define HHL_PWM_1 (EMIOS_0.CH[1].CBDR.R)
#define HHL_PWM_2 (EMIOS_0.CH[2].CBDR.R)
#define HHL_PWM_3 (EMIOS_0.CH[3].CBDR.R)
#define HHL_PWM_4 (EMIOS_0.CH[4].CBDR.R)
#define HHL_PWM_5 (EMIOS_0.CH[5].CBDR.R)
#define HHL_PWM_6 (EMIOS_0.CH[6].CBDR.R)
#define HHL_PWM_7 (EMIOS_0.CH[7].CBDR.R)
#define HHL_PWM_10 (EMIOS_0.CH[10].CBDR.R)
#define HHL_PWM_11 (EMIOS_0.CH[11].CBDR.R)
#define HHL_PWM_12 (EMIOS_0.CH[12].CBDR.R)
#define HHL_PWM_13 (EMIOS_0.CH[13].CBDR.R)
#define HHL_PWM_14 (EMIOS_0.CH[14].CBDR.R)
#define HHL_PWM_15 (EMIOS_0.CH[15].CBDR.R)

extern void init_hehelight(void);
extern void hehelighton(void);
extern void hehelightoff(void);
extern void init_hehelight_PWM(void);


#endif