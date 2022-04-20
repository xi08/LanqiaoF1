// code = utf-8
#include "sysTime.h"

/**
 * @brief 全局毫秒计时计数器
 *
 */
volatile uint32_t sysTime;

/**
 * @brief 全局计时标记
 *
 */
volatile uint8_t timeFlag;

/**
 * @brief 初始化系统时钟
 *
 */
void sysTimeInit(void)
{
    /* 2us延迟时钟 */
    TIM_TimeBaseInitTypeDef initStruct_TIM;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 开启TIM4
    initStruct_TIM.TIM_Period = 1;                       // 设置周期为2
    initStruct_TIM.TIM_Prescaler = 71;                   // 设置为72分频
    initStruct_TIM.TIM_CounterMode = TIM_CounterMode_Up; // 设置为向上计数
    TIM_TimeBaseInit(TIM4, &initStruct_TIM);             // 写入对应寄存器

    /* 1ms通用时钟 */
    sysTime = 0;                            // 清空计数器值
    SysTick_Config(SystemCoreClock / 1000); // 配置SysTick为1ms产生一次中断
    NVIC_SetPriority(SysTick_IRQn, 1);      // 配置SysTick为最高中断优先
}

/**
 * @brief 硬件毫秒延迟
 *
 * @param t 延迟 t 毫秒
 */
void delay1ms(uint32_t t)
{
    uint32_t delay1msStartTimestamp = sysTime, delayTime = t;
    if (delayTime < 0xffffffff)
        delayTime++;
    while (sysTime - delay1msStartTimestamp < delayTime)
        ;
}

/**
 * @brief 硬件微秒延迟
 *
 * @param t 延迟 2*t 微秒
 */
void delay2us(uint32_t t)
{
    while (t--)
    {
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);
        TIM_Cmd(TIM4, ENABLE);
        while (TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == RESET)
            ;
    }
}
