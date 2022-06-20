// code = utf-8
#include "key.h"
#include "sysTime.h"

/**
 * @brief 等待确认状态进入时间戳
 *
 */
uint32_t keyPressTimestamp[keyNum];

/**
 * @brief 按键状态枚举
 *
 */
keyState_enum keyState[keyNum];

/**
 * @brief 按键初始化
 *
 */
void keyInit(void)
{
    GPIO_InitTypeDef keyStruct_GPIO;

    /* GPIO时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟

    /* 工作模式设置 */
    keyStruct_GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 设置为浮空输入

    /* 配置Key0，Key2 */
    keyStruct_GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8; // 设置引脚号
    GPIO_Init(GPIOA, &keyStruct_GPIO);                 // 配置引脚

    /* 配置Key3，Key4 */
    keyStruct_GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; // 设置引脚号
    GPIO_Init(GPIOB, &keyStruct_GPIO);                 // 配置引脚
}
/**
 * @brief 更新按键信息
 *
 */
void updateKey(void)
{
    uint8_t i = keyNum, keyInfo = 0xff;

    /* 获取按键信息 */
    keyInfo ^= (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) << 0);
    keyInfo ^= (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) << 1);
    keyInfo ^= (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) << 2);
    keyInfo ^= (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) << 3);

    /* 按键信息转换 */
    while (i--)
    {
        // 按键按下
        if (keyInfo & (1 << i))
        {
            switch (keyState[i])
            {
            /* 未按下状态 */
            case S0:
                keyState[i] = S2;               // 状态切换
                keyPressTimestamp[i] = sysTime; // 更新时间戳
                break;

            default:
                break;
            }
        }
        // 按键抬起
        if (!(keyInfo & (1 << i)))
        {
            switch (keyState[i])
            {
            /* 已按下状态 */
            case S2:
                if (sysTime - keyPressTimestamp[i] >= keyLongPressTime)       // 长按检测
                    keyState[i] = S3;                                         // 状态切换
                else if (sysTime - keyPressTimestamp[i] >= keyShortPressTime) // 短按检测
                    keyState[i] = S1;                                         // 状态切换
                else
                    keyState[i] = S0; // 状态清除
                break;

            default:
                keyState[i] = S0; // 状态清除
                break;
            }
        }
    }
}
