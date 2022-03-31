// code = utf-8 
#ifndef __sysTime_h
#define __sysTime_h
#include "stm32f10x_conf.h"

extern volatile uint32_t sysTime;

void sysTimeInit(void);
void delay1ms(uint32_t t);
void delay2us(uint32_t t);

#endif
