// code = utf-8
#ifndef __pwm_h
#define __pwm_h
#include "stm32f10x_conf.h"

void pwmOutputInit_PA1(uint32_t freq, uint16_t duty);
void pwmChangeOutputFreq_PA1(uint32_t freq);
void pwmChangeOutputDuty_PA1(uint16_t duty);

void pwmInputInit_PA7(void);
void pwmGetInputPWM_PA7(uint32_t *freq, uint16_t *duty);
void pwmSWGetInputPWM_PA7(uint32_t *freq, uint16_t *duty);

#endif
