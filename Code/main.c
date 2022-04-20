// code = utf-8

#include "stm32f10x_conf.h"

#include "at24c02.h"
#include "buzz.h"
#include "key.h"
#include "lcd.h"
#include "led.h"
#include "r37.h"
#include "sysTime.h"
#include "uart.h"
#include "pwm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint16_t r37FilterValue;           // 旋转电位器滤波后值
uint16_t r37ValueMax, r37ValueMin; // 旋转电位器原始极值
float r37Val;                      // 旋转电位器转换后值

int main()
{
    uint8_t i;

    sysTimeInit();       // 初始化硬件延时时钟
    uart2Init(1152000);  // 初始化USB串口
    STM3210B_LCD_Init(); // 初始化显示
    LCD_Clear(White);    // 清屏
    keyInit();           // 初始化按键
    ledInit();           // 初始化LED管
    r37DmaInit();        // 初始化旋转电位器
    at24c02_init();      // 初始化E2PROM

    while (1)
    {
        /* 按键 */
        updateKey();
        keyProg();

        /* 串口1接收 */
        if (uartRxBufferDirtyFlag & (1 << 0))
        {
        }

        /* 串口2接收 */
        if (uartRxBufferDirtyFlag & (1 << 1))
        {
        }

        /* 1s定时执行 */
        if (timeFlag & (1 << 0))
        {
            timeFlag &= ~(1 << 0);
            printf("%.2f\n", r37Val);
        }

        /* 旋转电位器转换 */
        if (DMA_GetFlagStatus(DMA1_FLAG_TC1))
        {
            // 清空滤波缓存区
            r37ValueMax = 0;
            r37ValueMin = 0xffff;
            r37FilterValue = 0;
            // 滤波
            for (i = 0; i < 10; i++)
            {
                r37FilterValue += r37_ADCVal[i];
                if (r37_ADCVal[i] > r37ValueMax)
                    r37ValueMax = r37_ADCVal[i];
                if (r37_ADCVal[i] < r37ValueMin)
                    r37ValueMin = r37_ADCVal[i];
            }
            r37FilterValue -= r37ValueMax;
            r37FilterValue -= r37ValueMin;
            r37FilterValue >>= 3;
            // 转换
            r37Val = 3.3 * (float)r37FilterValue / 4095;
        }
    }
}
/**
 * @brief 按键响应
 *
 */
void keyProg(void)
{
    switch (keyState[0]) // KEY0, B1
    {
    case S1: // 短按

        break;
    case S3: // 长按
    case S4:

        break;
    default:
        break;
    }

    switch (keyState[1]) // KEY1, B2
    {
    case S1: // 短按

        break;
    case S3: // 长按
    case S4:

        break;
    default:
        break;
    }

    switch (keyState[2]) // KEY2, B3
    {
    case S1: // 短按

        break;
    case S3: // 长按
    case S4:

        break;
    default:
        break;
    }

    switch (keyState[3]) // KEY3, B4
    {
    case S1: // 短按

        break;
    case S3: // 长按
    case S4:

        break;
    default:
        break;
    }
}
