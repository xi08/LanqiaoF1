// code = utf-8 
#ifndef __uart_h
#define __uart_h
#include "stm32f10x_conf.h"

#define uartRxBufferSize 16
#define uartNum 2

#define uartStopSymbol '\r' // 通信末尾标志

/**
 * @brief 串口接收缓冲区
 *
 */
extern uint8_t uartRxBuffer[uartNum][uartRxBufferSize];

/**
 * @brief 缓冲区使用计数
 *
 */
extern uint8_t uartRxBufferIdx[uartNum];

/**
 * @brief 缓冲区覆写标记
 *
 */
extern uint8_t uartRxBufferDirtyFlag;

void uart1Init(uint32_t baudRate);
void uart2Init(uint32_t baudRate);
uint8_t uartSendChar(USART_TypeDef *commPort, uint8_t Char);
void uartSend(USART_TypeDef *commPort, uint8_t *Str);

#endif
