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

#define tF_1ms (0x01)
#define tF_10ms (0x02)
#define tF_100ms (0x04)
#define tF_1000ms (0x08)

void sysTimeInit(void);
void delay1ms(uint32_t t);
void delay2us(uint32_t t);

#endif
