// code = utf-8 

#ifndef __r37_h
#define __r37_h
#include "stm32f10x_conf.h"


extern uint16_t r37_ADCVal[16];

void r37Init(void);
void r37DmaInit(void);

uint16_t r37SingleConj(void);

#endif
