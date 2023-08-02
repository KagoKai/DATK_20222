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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DI2_Pin GPIO_PIN_4
#define DI2_GPIO_Port GPIOA
#define DI1_Pin GPIO_PIN_6
#define DI1_GPIO_Port GPIOA
#define ss_left_top_Pin GPIO_PIN_7
#define ss_left_top_GPIO_Port GPIOA
#define ss_left_mid_Pin GPIO_PIN_0
#define ss_left_mid_GPIO_Port GPIOB
#define ss_left_bot_Pin GPIO_PIN_1
#define ss_left_bot_GPIO_Port GPIOB
#define AL2_Pin GPIO_PIN_8
#define AL2_GPIO_Port GPIOA
#define AL1_Pin GPIO_PIN_9
#define AL1_GPIO_Port GPIOA
#define AL4_Pin GPIO_PIN_10
#define AL4_GPIO_Port GPIOA
#define AL3_Pin GPIO_PIN_11
#define AL3_GPIO_Port GPIOA
#define DI4_Pin GPIO_PIN_3
#define DI4_GPIO_Port GPIOB
#define DI3_Pin GPIO_PIN_5
#define DI3_GPIO_Port GPIOB
#define ss_right_bot_Pin GPIO_PIN_6
#define ss_right_bot_GPIO_Port GPIOB
#define ss_right_mid_Pin GPIO_PIN_7
#define ss_right_mid_GPIO_Port GPIOB
#define ss_right_top_Pin GPIO_PIN_8
#define ss_right_top_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
