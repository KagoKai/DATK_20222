#include "Dong_co.h"

void Pwm_control(TIM_HandleTypeDef *htim, uint32_t Channel,uint8_t Speed){
uint16_t duty = (uint16_t)Speed*(htim->Instance->ARR)/100;
	switch(Channel){
		case TIM_CHANNEL_1 :
    htim->Instance->CCR1= duty;
		break;
		case TIM_CHANNEL_2 :
    htim->Instance->CCR2= duty;
		break;
		case TIM_CHANNEL_3 :
    htim->Instance->CCR3= duty;
		break;
		case TIM_CHANNEL_4 :
    htim->Instance->CCR4= duty;
		break;
	}	
};
void DC_Control(Dong_co_typedef *dong_co, DC_Status Status ,uint8_t Speed){
dong_co->dc_status= Status;
switch(Status){
	case DC_Stop:
	HAL_GPIO_WritePin(dong_co->GPIOx, dong_co->GPIO_Pin, 0);
	Pwm_control(dong_co->htim,dong_co->TIM_CHANNEL,0);
	break;
	case DC_Back: //  out1 van lon hon out2
	HAL_GPIO_WritePin(dong_co->GPIOx, dong_co->GPIO_Pin,1 );
	Pwm_control(dong_co->htim,dong_co->TIM_CHANNEL,100-Speed);
	break;
	case DC_Forwork:
	HAL_GPIO_WritePin(dong_co->GPIOx,dong_co->GPIO_Pin, 0);
	Pwm_control(dong_co->htim,dong_co->TIM_CHANNEL,Speed);
	break;
}
};

void DC_Init(Dong_co_typedef *dong_co, GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin, TIM_HandleTypeDef *htim, uint32_t Channel){
dong_co->GPIOx = GPIOx;
dong_co->GPIO_Pin= GPIO_Pin;
dong_co->htim= htim;
dong_co->TIM_CHANNEL= Channel;
HAL_TIM_PWM_Start(dong_co->htim, dong_co->TIM_CHANNEL);
};
