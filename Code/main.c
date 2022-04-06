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

#include <string.h>
#include <stdlib.h>

uint16_t r37FilterValue; // 旋转电位器滤波后值
float r37Val;            // 旋转电位器转换后值

int main()
{
    uint8_t i;

    sysTimeInit();
    uart2Init(115200);
    STM3210B_LCD_Init();
    LCD_Clear(White);

    keyInit();
    ledInit();
    r37DmaInit();
    at24c02_init();

    while (1)
    {
        /* 按键查询 */
        updateKey();
        keyProg();

        /* 旋转电位器转换 */
        if (DMA_GetFlagStatus(DMA1_FLAG_TC1))
        {
            r37FilterValue = 0;
            for (i = 0; i < 16; i++)
                r37FilterValue += r37_ADCVal[i];
            r37FilterValue >>= 4;
            r37Val = 3.3 * (float)r37FilterValue / 4095;
        }
    }
}

void keyProg(void)
{
    // key0
    switch (keyState[0])
    {
    case S1:

        break;
    case S3:
    case S4:

        break;
    default:
        break;
    }
    // key1
    switch (keyState[1])
    {
    case S1:

        break;
    case S3:
    case S4:

        break;
    default:
        break;
    }
    // key2
    switch (keyState[2])
    {
    case S1:

        break;
    case S3:
    case S4:

        break;
    default:
        break;
    }
    // key3
    switch (keyState[3])
    {
    case S1:

        break;
    case S3:
    case S4:

        break;
    default:
        break;
    }
}
