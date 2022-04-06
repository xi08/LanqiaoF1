// code = utf-8 
#ifndef __pwm_h
#define __pwm_h
#include "stm32f10x_conf.h"

void pwmOutputPA6(uint32_t freq,uint16_t duty);

void pwmOutputPA9(uint32_t freq,uint16_t duty);

void pwmOutputPA1(uint32_t freq,uint16_t duty);

void pwmCapturePA6(uint32_t freq,uint16_t duty);

void pwmCapturePA1(uint32_t freq,uint16_t duty);

void pwmCapturePA9(uint32_t freq,uint16_t duty);



#endif
