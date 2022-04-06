// code = utf-8 
#ifndef __i2c_h
#define __i2c_h
#include "stm32f10x_conf.h"

void i2cInit(void);
void i2cReset(void);

void i2cSTART(void);
void i2cSTOP(void);
void i2cACK(void);
void i2cNACK(void);
uint8_t i2cWaitACK(void);

void i2cSend(uint8_t data);
uint8_t i2cReceive(void);




#endif
