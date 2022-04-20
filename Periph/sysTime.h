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

void sysTimeInit(void);
void delay1ms(uint32_t t);
void delay2us(uint32_t t);

#endif
