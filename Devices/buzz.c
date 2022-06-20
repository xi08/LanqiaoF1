// code = utf-8

#include "buzz.h"

/**
 * @brief 蜂鸣器初始化
 *
 */
void buzzInit(void)
{
    GPIO_InitTypeDef buzzStruct;

    /* 设置时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 使能复用时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);  // 关闭JTAG的TRST引脚功能

    /* 设置引脚 */
    buzzStruct.GPIO_Pin = GPIO_Pin_4;         // 引脚号
    buzzStruct.GPIO_Speed = GPIO_Speed_50MHz; // 引脚速度
    buzzStruct.GPIO_Mode = GPIO_Mode_Out_PP;  // 引脚功能
    GPIO_Init(GPIOB, &buzzStruct);            // 设置引脚
}
/**
 * @brief 切换蜂鸣器状态
 *
 * @param status 蜂鸣器目标状态
 */
void buzz(uint8_t status)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)(!status));
}
