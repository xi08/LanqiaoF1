// code = utf-8

#include "r37.h"

/**
 * @brief 旋转电位器DMA采集结果
 * 
 */
uint16_t r37_ADCVal[10];

/**
 * @brief 旋转电位器DMA采集初始化
 *
 */
void r37DmaInit(void)
{
    ADC_InitTypeDef initStruct_ADC;
    DMA_InitTypeDef initStruct_DMA;
    GPIO_InitTypeDef initStruct_GPIO;

    /* DMA配置 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                       // 开启DMA1时钟
    DMA_DeInit(DMA1_Channel1);                                               // 关闭DMA1通道1
    initStruct_DMA.DMA_M2M = DMA_M2M_Disable;                                // 设置为非内存到内存的DMA
    initStruct_DMA.DMA_PeripheralBaseAddr = (ADC1_BASE + 0x4c);              // 设置外设地址为ADC1规则通道转换结果寄存器
    initStruct_DMA.DMA_MemoryBaseAddr = (uint32_t)r37_ADCVal;                // 设置内存地址
    initStruct_DMA.DMA_DIR = DMA_DIR_PeripheralSRC;                          // 设置DMA传输方向为外设到内存
    initStruct_DMA.DMA_BufferSize = 10;                                      // 设置DMA缓冲区空间
    initStruct_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            // 设置为关闭外设地址自动递增
    initStruct_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable;                     // 设置为开启内存地址自动递增
    initStruct_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 设置外设数据宽度为半字
    initStruct_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 设置内存数据宽度为半字
    initStruct_DMA.DMA_Mode = DMA_Mode_Circular;                             // 设置为循环传输
    initStruct_DMA.DMA_Priority = DMA_Priority_High;                         // 设置DMA优先级为高
    DMA_Init(DMA1_Channel1, &initStruct_DMA);                                // 写入DMA1设置
    DMA_Cmd(DMA1_Channel1, ENABLE);                                          // 使能DMA1

    /* GPIO配置 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB时钟
    initStruct_GPIO.GPIO_Pin = GPIO_Pin_0;                // 设置旋转电位器引脚
    initStruct_GPIO.GPIO_Mode = GPIO_Mode_AIN;            // 设置引脚工作模式为模拟输入
    GPIO_Init(GPIOB, &initStruct_GPIO);                   // 写入GPIOB设置

    /* ADC配置 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);             // 开启ADC1时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                // 设置工作频率为6分频 (@12MHz)
    initStruct_ADC.ADC_Mode = ADC_Mode_Independent;                  // 设置为独立模式
    initStruct_ADC.ADC_ScanConvMode = DISABLE;                       // 设置扫描模式为关
    initStruct_ADC.ADC_ContinuousConvMode = ENABLE;                  // 设置为连续转换模式
    initStruct_ADC.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 关闭外部触发
    initStruct_ADC.ADC_DataAlign = ADC_DataAlign_Right;              // 设置为右对齐
    initStruct_ADC.ADC_NbrOfChannel = 1;                             // 设置规则通道数
    ADC_Init(ADC1, &initStruct_ADC);                                 // 写入ADC1设置

    /* ADC通道配置 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_7Cycles5); // 设置ADC1CH8采样周期为7.5

    ADC_DMACmd(ADC1, ENABLE); // 使能ADC1的DMA
    ADC_Cmd(ADC1, ENABLE);    // 使能ADC1

    ADC_StartCalibration(ADC1); // 开始ADC1自校准
    while (ADC_GetCalibrationStatus(ADC1))// 等待ADC1自校准结束
        ;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 软件触发首次ADC1转换
}

/**
 * @brief 旋转电位器采集初始化
 *
 */
void r37Init(void)
{
    ADC_InitTypeDef initStruct_ADC;
    GPIO_InitTypeDef initStruct_GPIO;

    /* GPIO配置 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB时钟
    initStruct_GPIO.GPIO_Pin = GPIO_Pin_0;                // 设置旋转电位器引脚
    initStruct_GPIO.GPIO_Mode = GPIO_Mode_AIN;            // 设置引脚工作模式为模拟输入
    GPIO_Init(GPIOB, &initStruct_GPIO);                   // 写入GPIOB设置

    /* ADC配置 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);             // 开启ADC1时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                // 设置工作频率为6分频 (@12MHz)
    initStruct_ADC.ADC_Mode = ADC_Mode_Independent;                  // 设置为独立模式
    initStruct_ADC.ADC_ScanConvMode = DISABLE;                       // 设置扫描模式为关
    initStruct_ADC.ADC_ContinuousConvMode = ENABLE;                  // 设置为连续转换模式
    initStruct_ADC.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 关闭外部触发
    initStruct_ADC.ADC_DataAlign = ADC_DataAlign_Right;              // 设置为右对齐
    initStruct_ADC.ADC_NbrOfChannel = 1;                             // 设置规则通道数
    ADC_Init(ADC1, &initStruct_ADC);                                 // 写入ADC1设置

    /* ADC通道配置 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_7Cycles5); //设置ADC1CH8采样周期为7.5

    ADC_Cmd(ADC1, ENABLE); // 使能ADC1

    /* ADC自校准 */
    ADC_StartCalibration(ADC1);            // 触发ADC1自校准
    while (ADC_GetCalibrationStatus(ADC1)) // 等待ADC1自校准结束
        ;
}

/**
 * @brief 旋转电位器单次采集
 *
 * @return uint16_t 采集值, 0-4095
 */
uint16_t r37SingleConj(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 触发转换
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        ;                                // 等待转换完成
    return ADC_GetConversionValue(ADC1); // 返回转换结果
}
