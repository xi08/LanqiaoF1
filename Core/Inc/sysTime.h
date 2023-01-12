// code = utf-8
#ifndef __sysTime_h
#define __sysTime_h
#include "stm32f10x_conf.h"

/**
 * @brief 全局毫秒计时计数器
 *
 */
extern volatile uint32_t sysTime;

/**
 * @brief 全局计时标记
 *
 */
extern volatile uint8_t timeFlag;

#define tF_1ms 1
#define tF_10ms 2
#define tF_100ms 4
#define tF_1000ms 8
#define tF_5ms 16
#define tF_50ms 32
#define tF_500ms 64
#define tF_30Hz 128


void sysTimeInit(void);
void delay1ms(uint32_t t);
void delay2us(uint32_t t);

#endif
