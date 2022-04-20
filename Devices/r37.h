// code = utf-8

#ifndef __r37_h
#define __r37_h
#include "stm32f10x_conf.h"

/**
 * @brief 旋转电位器DMA采集结果
 *
 */
extern uint16_t r37_ADCVal[10];

void r37Init(void);
void r37DmaInit(void);

uint16_t r37SingleConj(void);

#endif
