// code = utf-8

#include "buzz.h"

/**
 * @brief 蜂鸣器初始化
 *
 */
void buzzInit(void)
{
    GPIO_InitTypeDef initStruct_gpio;

    /* 设置时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 使能复用时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);  // 关闭JTAG的TRST引脚功能

    /* 设置引脚 */
    initStruct_gpio.GPIO_Pin = GPIO_Pin_4;         // 设置引脚号
    initStruct_gpio.GPIO_Speed = GPIO_Speed_50MHz; // 设置引脚速度
    initStruct_gpio.GPIO_Mode = GPIO_Mode_Out_PP;  // 设置引脚为普通推挽输出
    GPIO_Init(GPIOB, &initStruct_gpio);            // 配置引脚
}
/**
 * @brief 切换蜂鸣器状态
 *
 * @param status 蜂鸣器目标状态
 */
void buzz(uint8_t status)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)(!status)); // 切换
}
