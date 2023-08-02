#ifndef DONG_CO_H
#define DONG_CO_H
#include "stm32f1xx.h"
typedef enum
	{DC_Stop,
	 DC_Forwork,
	 DC_Back,
	} DC_Status;

typedef struct{
DC_Status dc_status;
GPIO_TypeDef *GPIOx;
uint16_t GPIO_Pin;
TIM_HandleTypeDef *htim;
uint32_t TIM_CHANNEL;
} Dong_co_typedef; 
void Pwm_control(TIM_HandleTypeDef *htim, uint32_t Channel,uint8_t Speed);
void DC_Control(Dong_co_typedef *dong_co, DC_Status Status ,uint8_t Speed);
void DC_Init(Dong_co_typedef *dong_co, GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin, TIM_HandleTypeDef *htim, uint32_t Channel);
#endif
