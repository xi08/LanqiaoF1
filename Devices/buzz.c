// code = utf-8 

#include "buzz.h"

/**
 * @brief 蜂鸣器初始化
 *
 */
void buzzInit(void)
{
    GPIO_InitTypeDef buzzStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    buzzStruct.GPIO_Pin = GPIO_Pin_4;
    buzzStruct.GPIO_Speed = GPIO_Speed_50MHz;
    buzzStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &buzzStruct);
}
/**
 * @brief 切换蜂鸣器状态
 *
 * @param status 蜂鸣器目标状态
 */
void buzz(uint8_t status)
{
    if (status)
        GPIO_ResetBits(GPIOB, GPIO_Pin_4);
    else
        GPIO_SetBits(GPIOB, GPIO_Pin_4);
}
