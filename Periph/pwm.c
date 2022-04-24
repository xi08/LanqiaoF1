// code = utf-8

#include "pwm.h"

/**
 * @brief 在PA1上输出PWM波
 *
 * @param freq 频率
 * @param duty 占空比，0%到100.0%
 */
void pwmOutputInit_PA1(uint32_t freq, uint16_t duty)
{
    uint16_t tbPrescaler = ((SystemCoreClock / freq) >> 16);
    uint16_t tbPeriod = (SystemCoreClock / freq) / (tbPrescaler + 1) - 1;
    uint16_t ocPluse = tbPeriod * duty / 10000;

    GPIO_InitTypeDef initStruct_gpio;
    TIM_TimeBaseInitTypeDef initStruct_timBase;
    TIM_OCInitTypeDef initStruct_timOutput;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    initStruct_gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    initStruct_gpio.GPIO_Pin = GPIO_Pin_1;
    initStruct_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &initStruct_gpio);

    initStruct_timBase.TIM_CounterMode = TIM_CounterMode_Up;
    initStruct_timBase.TIM_ClockDivision = TIM_CKD_DIV1;
    initStruct_timBase.TIM_RepetitionCounter = 0;
    initStruct_timBase.TIM_Prescaler = tbPrescaler;
    initStruct_timBase.TIM_Period = tbPeriod;
    TIM_TimeBaseInit(TIM2, &initStruct_timBase);

    initStruct_timOutput.TIM_OCMode = TIM_OCMode_PWM1;
    initStruct_timOutput.TIM_OCPolarity = TIM_OCPolarity_High;
    initStruct_timOutput.TIM_OutputState = TIM_OutputState_Enable;
    initStruct_timOutput.TIM_OCNPolarity = TIM_OutputNState_Disable;
    initStruct_timOutput.TIM_Pulse = ocPluse;
    TIM_OC2Init(TIM2, &initStruct_timOutput);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief 修改PA1上输出PWM波的频率
 *
 * @param freq 频率
 */
void pwmChangeOutputFreq_PA1(uint32_t freq)
{
    uint16_t newPrescaler = ((SystemCoreClock / freq) >> 16);
    uint16_t newPeriod = (SystemCoreClock / freq) / (newPrescaler + 1) - 1;
    TIM_PrescalerConfig(TIM2, newPrescaler, TIM_PSCReloadMode_Update);
    TIM_SetAutoreload(TIM2, newPeriod);
}

/**
 * @brief 修改PA1上输出PWM波的占空比
 *
 * @param duty 占空比
 */
void pwmChangeOutputDuty_PA1(uint16_t duty)
{
    uint16_t newPluse = (TIM2->ARR) * duty / 10000;
    TIM_SetCompare2(TIM2, newPluse);
}

void pwmInputInit_PA7(void)
{
    GPIO_InitTypeDef initStruct_gpio;
    TIM_TimeBaseInitTypeDef initStruct_timBase;
    TIM_ICInitTypeDef initStruct_timInput;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    initStruct_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    initStruct_gpio.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &initStruct_gpio);

    initStruct_timBase.TIM_CounterMode = TIM_CounterMode_Up;
    initStruct_timBase.TIM_ClockDivision = TIM_CKD_DIV1;
    initStruct_timBase.TIM_RepetitionCounter = 0;
    initStruct_timBase.TIM_Prescaler = 1099;
    initStruct_timBase.TIM_Period = 65535;
    TIM_TimeBaseInit(TIM3, &initStruct_timBase);

    initStruct_timInput.TIM_Channel = TIM_Channel_2;
    initStruct_timInput.TIM_ICPolarity = TIM_ICPolarity_Rising;
    initStruct_timInput.TIM_ICSelection = TIM_ICSelection_DirectTI;
    initStruct_timInput.TIM_ICFilter = 0;
    initStruct_timInput.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_PWMIConfig(TIM3, &initStruct_timInput);

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
    TIM_Cmd(TIM3, ENABLE);
}

/**
 * @brief
 *
 * @param freq
 * @param duty
 */
void pwmGetInputPWM_PA7(uint32_t *freq, uint16_t *duty)
{
    while (!TIM_GetFlagStatus(TIM3, TIM_FLAG_CC2))
        ;
    (*freq) = SystemCoreClock / (TIM3->PSC + 1) / (TIM3->CCR2 + 1) + 1;
    (*duty) = 10000 * (TIM3->CCR1 + 1) / (TIM3->CCR2 + 1);
}

/**
 * @brief
 *
 * @param freq
 * @param duty
 */
void pwmSWGetInputPWM_PA7(uint32_t *freq, uint16_t *duty)
{
    TIM_PrescalerConfig(TIM3, 1099, TIM_PSCReloadMode_Update);
    while (!TIM_GetFlagStatus(TIM3, TIM_FLAG_CC2))
        ;
    (*freq) = SystemCoreClock / (TIM3->PSC + 1) / (TIM3->CCR2 + 1) + 1;
    (*duty) = 10000 * (TIM3->CCR1 + 1) / (TIM3->CCR2 + 1);
    if (*freq >= 1000)
    {
        TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Update);
        while (!TIM_GetFlagStatus(TIM3, TIM_FLAG_CC2))
            ;
        (*freq) = SystemCoreClock / (TIM3->PSC + 1) / (TIM3->CCR2 + 1) + 1;
        (*duty) = 10000 * (TIM3->CCR1 + 1) / (TIM3->CCR2 + 1);
    }
}
