/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Car.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t data_rx;
Car_go_status car_go_status= Car_go_forward; // bien trang thai chi huong di cua xe
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//1->8 bat
	//A -> H tat
  
	HAL_UART_Receive_IT(&huart3,&data_rx,1);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
//DC_Init(&Right_Bot,GPIOA, GPIO_PIN_6,&htim1, TIM_CHANNEL_2);
//DC_Init(&Left_Bot,GPIOA, GPIO_PIN_4,&htim1, TIM_CHANNEL_1);
//DC_Init(&Left_Top,GPIOB, GPIO_PIN_5,&htim1, TIM_CHANNEL_4);
//DC_Init(&Right_Top,GPIOB, GPIO_PIN_3, &htim1, TIM_CHANNEL_3);
int ss_right_top=0;
int ss_left_top=1;
int ss_left_mid=0;
int ss_right_mid=1;
int ss_left_bot=0;
int ss_right_bot=0;
int turn=0; 
		char buff1[50];
		char buff2[50];
		char buff3[50];
		char buff4[50];
uint32_t Time= HAL_GetTick();
Car_Init(&htim1);
HAL_UART_Receive_IT(&huart3,&data_rx,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
ss_right_top= HAL_GPIO_ReadPin(ss_right_top_GPIO_Port, ss_right_top_Pin);
ss_left_top= HAL_GPIO_ReadPin(ss_left_top_GPIO_Port, ss_left_top_Pin);
ss_left_mid= HAL_GPIO_ReadPin(ss_left_mid_GPIO_Port, ss_left_mid_Pin);
ss_right_mid= HAL_GPIO_ReadPin(ss_right_mid_GPIO_Port, ss_right_mid_Pin);	
ss_right_bot= HAL_GPIO_ReadPin(ss_right_bot_GPIO_Port, ss_right_bot_Pin);
ss_left_bot= HAL_GPIO_ReadPin(ss_left_bot_GPIO_Port, ss_left_bot_Pin);
		
while((HAL_GetTick()- Time) <=10000);
//		int len1 = sprintf(buff1,"gia tri ss_right_top: %d\n",ss_right_top);
//		HAL_UART_Transmit(&huart3,(uint8_t *)buff1,len1,300);
//		int len2 = sprintf(buff2,"gia tri ss_left_top: %d\n",ss_left_top);
//		HAL_UART_Transmit(&huart3,(uint8_t *)buff2,len2,300);
//		int len3 = sprintf(buff3,"gia tri ss_left_mid: %d\n",ss_left_mid);
//		HAL_UART_Transmit(&huart3,(uint8_t *)buff3,len3,300);
//		int len4 = sprintf(buff4,"gia tri ss_right_mid: %d\n",ss_right_mid);
//		HAL_UART_Transmit(&huart3,(uint8_t *)buff4,len4,300);
//		HAL_Delay(1000);		

//if(turn==8){
//Car_control(Car_stop,25);
//if(data_rx== 'a'){ // tin hieu thoat Stop
//Car_control(Car_forwork,25);
//HAL_Delay(5000);
//turn=0;

//} 
//}		
		
if(car_go_status== Car_go_forward){    
if(ss_right_mid ==0 && ss_left_mid ==0){
	if(ss_right_top ==0 && ss_left_top ==0){
		// tram stop
		Car_control(Car_stop,25); // hoac lam vong lap o day, chi thoat khi nhan dc tins hieu data_rx== 'a'
		//turn=8; // bang 8 la tram stop
	}
	else if(ss_right_top ==0 && ss_left_top ==1){
		// di sang phai
		
		Car_control(Car_stop,25);
		HAL_Delay(3000);
		car_go_status=1;   // chuyn trang thai xe xang di phai
		Car_control(Car_move_right,25);
		//HAL_Delay(450);
		HAL_Delay(425);
	}
}
else{
	if(ss_right_top ==1 && ss_left_top ==1){
		Car_control(Car_forwork,25);
	}
	else if(ss_right_top ==0 && ss_left_top ==1){
		Car_control(Car_left,25);
	}
	else if(ss_right_top ==1 && ss_left_top ==0){
		Car_control(Car_right,25);
	}
	else{
    Car_control(Car_forwork,25);
	}
}
}

if(car_go_status==1){
if(ss_left_top ==0 && ss_left_mid ==0){
	if(ss_right_top ==0 && ss_right_mid ==0){
		// tram stop
		Car_control(Car_stop,30);
	}
	else if(ss_right_top ==1 && ss_right_mid ==0){
		// di xuong
		car_go_status=2;
		Car_control(Car_back,25);
		HAL_Delay(425);
	}
}
else{
	if(ss_right_top ==1 && ss_right_mid ==1){
		Car_control(Car_move_right,25);
	}
	else if(ss_right_top ==0 && ss_right_mid ==1){
		Car_control(Car_right,25);
	}
	else if(ss_right_top ==1 && ss_right_mid ==0){
		Car_control(Car_dc_right_back,25);
	}
	else{
    Car_control(Car_move_right,25);
	}
}
}

if(car_go_status ==2){
	// di xuong duoi
	if(ss_right_mid==0 && ss_left_mid ==0){
	if(ss_right_bot ==0 && ss_left_bot ==0){
	  Car_control(Car_stop,25);
	}
	else if(ss_right_bot ==1 && ss_left_bot ==0){
	  // xe di sang phai, chuyen trang thai
		Car_control(Car_stop,30);  // viet tam
	}
	}
	else{
	if(ss_right_bot ==1 && ss_left_bot ==1){
	Car_control(Car_back,25);
	}
	else if(ss_right_bot ==0 && ss_left_bot ==1){
	Car_control(Car_dc_left_back,25);
	}
	else if(ss_right_bot ==1 && ss_left_bot ==0){
	Car_control(Car_dc_right_back,25);
	}
	else{
	Car_control(Car_back,25);
	}
		}
}
// di sang trai
if(car_go_status== 3){
 if(ss_right_mid==0 && ss_right_bot==0){
	 if(ss_left_mid==0 && ss_left_bot==0){
		 Car_control(Car_stop,25); // tram stop
	 }
 }
 else{
 if(ss_left_mid==1 && ss_left_bot==1){
 Car_control(Car_move_left,25);  
 }
 else if(ss_left_mid==0 && ss_left_bot==1){
 Car_control(Car_left,25);
 }
 else if(ss_left_mid==1 && ss_left_bot==0){
 Car_control(Car_dc_left_back,25);
 }
 else{
 Car_control(Car_move_left,25);  
 }
 }
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 63;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DI2_Pin|DI1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DI4_Pin|DI3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DI2_Pin DI1_Pin */
  GPIO_InitStruct.Pin = DI2_Pin|DI1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ss_left_top_Pin */
  GPIO_InitStruct.Pin = ss_left_top_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ss_left_top_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ss_left_mid_Pin ss_left_bot_Pin ss_right_bot_Pin ss_right_mid_Pin
                           ss_right_top_Pin */
  GPIO_InitStruct.Pin = ss_left_mid_Pin|ss_left_bot_Pin|ss_right_bot_Pin|ss_right_mid_Pin
                          |ss_right_top_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DI4_Pin DI3_Pin */
  GPIO_InitStruct.Pin = DI4_Pin|DI3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
