/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern volatile uint32_t sysTime;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD6_Pin LL_GPIO_PIN_13
#define LD6_GPIO_Port GPIOC
#define LD7_Pin LL_GPIO_PIN_14
#define LD7_GPIO_Port GPIOC
#define LD8_Pin LL_GPIO_PIN_15
#define LD8_GPIO_Port GPIOC
#define B1_Pin LL_GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define B2_Pin LL_GPIO_PIN_1
#define B2_GPIO_Port GPIOA
#define R37_Pin LL_GPIO_PIN_0
#define R37_GPIO_Port GPIOB
#define B3_Pin LL_GPIO_PIN_1
#define B3_GPIO_Port GPIOB
#define B4_Pin LL_GPIO_PIN_2
#define B4_GPIO_Port GPIOB
#define LD1_Pin LL_GPIO_PIN_8
#define LD1_GPIO_Port GPIOC
#define LD2_Pin LL_GPIO_PIN_9
#define LD2_GPIO_Port GPIOC
#define TXD1_Pin LL_GPIO_PIN_9
#define TXD1_GPIO_Port GPIOA
#define RXD1_Pin LL_GPIO_PIN_10
#define RXD1_GPIO_Port GPIOA
#define LD3_Pin LL_GPIO_PIN_10
#define LD3_GPIO_Port GPIOC
#define LD4_Pin LL_GPIO_PIN_11
#define LD4_GPIO_Port GPIOC
#define LD5_Pin LL_GPIO_PIN_12
#define LD5_GPIO_Port GPIOC
#define LE_Pin LL_GPIO_PIN_2
#define LE_GPIO_Port GPIOD
#define BUZ_Pin LL_GPIO_PIN_4
#define BUZ_GPIO_Port GPIOB
#define SCL_Pin LL_GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin LL_GPIO_PIN_7
#define SDA_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
