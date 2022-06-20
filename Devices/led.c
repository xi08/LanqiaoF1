// code = utf-8
#include "led.h"

/**
 * @brief LED初始化
 *
 */
void ledInit(void)
{
    GPIO_InitTypeDef initStruct_gpio;

    /* 时钟设置 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 使能GPIOC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // 使能GPIOD时钟

    /* LED与锁存器设置 */
    initStruct_gpio.GPIO_Speed = GPIO_Speed_2MHz; // 设置引脚速率
    initStruct_gpio.GPIO_Mode = GPIO_Mode_Out_PP; // 设置引脚为普通推挽输出
    initStruct_gpio.GPIO_Pin = 0xff00;            // 设置LED灯引脚
    GPIO_Init(GPIOC, &initStruct_gpio);           // 配置LED灯引脚
    initStruct_gpio.GPIO_Pin = GPIO_Pin_2;        // 设置锁存器控制引脚
    GPIO_Init(GPIOD, &initStruct_gpio);           // 配置锁存器控制引脚
}

/**
 * @brief 同步LED显示序列
 *
 * @param status LED显示序列
 */
void ledDisp(uint8_t status)
{
    /* 设置引脚电平 */
    GPIO_Write(GPIOC, ~status << 8);

    /* 刷新引脚 */
    GPIO_SetBits(GPIOD, GPIO_Pin_2);
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}
