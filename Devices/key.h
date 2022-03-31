// code = utf-8 
#ifndef __key_h
#define __key_h
#include "stm32f10x_conf.h"

// 按键数量
#define keyNum 4
//长按所需时长 (ms)
#define keyLongPressTime 800
//短按所需时长 (ms)
#define keyShortPressTime 50

/**
 * @brief 按键状态枚举
 * 
 */
typedef enum
{
    S0, // 抬起
    S1, // 短按
    S2, // 按下
    S3, // 长按
    S4, // 满足长按所需周期但未抬起
} keyState_enum;
extern keyState_enum keyState[keyNum];

void keyInit(void);
void updateKey(void);
void keyProg(void);
#endif
