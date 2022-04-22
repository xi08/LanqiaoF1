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

// 旋转电位器滤波前缓冲
uint16_t r37FilterValue, r37FilterMax, r37FilterMin;
// 旋转电位器标记位
uint8_t r37Flag;
// 旋转电位器转换后当前值
float r37Val;
// 旋转电位器转换后上一次值
float r37Val_1;

// 显示缓冲
uint8_t dispBuffer[21];

int main()
{
    uint8_t i;

    sysTimeInit();       // 初始化硬件延时时钟
    uart2Init(1152000);  // 初始化USB串口
    STM3210B_LCD_Init(); // 初始化显示
    LCD_Clear(White);    // 清屏
    keyInit();           // 初始化按键
    ledInit();           // 初始化LED管
    ledDisp(0x0);        // 清除LED显示
    r37DmaInit();        // 初始化旋转电位器
    at24c02_init();      // 初始化E2PROM

    LCD_DisplayStringLine(Line0, "CT117E V1.1");
    LCD_DisplayStringLine(Line1, "Compiled in");
    sprintf((char *)dispBuffer, "%s,%s", __TIME__, __DATE__);
    LCD_DisplayStringLine(Line2, dispBuffer);
    printf("%s\n%s:%s\n", "CT117E V1.1", "Compiled in", dispBuffer);
    delay1ms(1000);
    LCD_ClearLine(Line1);
    LCD_ClearLine(Line2);
    while (1)
    {

        // 按键
        updateKey();
        keyProg();

        // 串口2接收
        if (uartRxBufferDirtyFlag & (1 << 1))
        {
            LCD_DisplayStringLine(Line2, uartRxBuffer[1]);
        }

        // 1s定时执行
        if (timeFlag & tF_1000ms)
        {
            timeFlag &= ~tF_1000ms;
            // 输出旋转电位器转换值
            if (r37Flag & (1 << 0))
            {
                sprintf((char *)dispBuffer, "r37=%.2fV", r37Val);
                printf("%s\n", dispBuffer);
                LCD_DisplayStringLine(Line1, dispBuffer);
            }
        }

        //  旋转电位器转换
        if (DMA_GetFlagStatus(DMA1_FLAG_TC1))
        {
            // 清空滤波缓存区
            r37FilterMax = 0;
            r37FilterMin = 0xffff;
            r37FilterValue = 0;
            // 写入上一次结果
            r37Val_1 = r37Val;
            // 滤波
            for (i = 0; i < 10; i++)
            {
                r37FilterValue += r37_ADCVal[i];
                if (r37_ADCVal[i] > r37FilterMax)
                    r37FilterMax = r37_ADCVal[i];
                if (r37_ADCVal[i] < r37FilterMin)
                    r37FilterMin = r37_ADCVal[i];
            }
            r37FilterValue -= r37FilterMax;
            r37FilterValue -= r37FilterMin;
            r37FilterValue >>= 3;
            // 转换
            r37Val = 3.3 * (float)r37FilterValue / 4095;
            // 设置标记位
            r37Flag |= (1 << 0);
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
