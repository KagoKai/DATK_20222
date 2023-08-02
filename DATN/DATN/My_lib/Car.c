#include "Car.h"
#include "Dong_co.h"

Dong_co_typedef Right_Top;
Dong_co_typedef Left_Top;
Dong_co_typedef Right_Bot;
Dong_co_typedef Left_Bot;
void Car_control(Car_Status car_status ,uint8_t speed){
switch(car_status){
	case Car_forwork :
	DC_Control(&Right_Top, DC_Forwork, speed);
	DC_Control(&Left_Top, DC_Forwork, speed);
	DC_Control(&Right_Bot, DC_Forwork, speed);
	DC_Control(&Left_Bot, DC_Forwork, speed);
	break;
	case Car_back:
	DC_Control(&Right_Top, DC_Back, speed);
	DC_Control(&Left_Top, DC_Back, speed);	
	DC_Control(&Right_Bot, DC_Back, speed);
	DC_Control(&Left_Bot, DC_Back, speed);	
	break;
	case Car_stop:
	DC_Control(&Right_Top, DC_Stop, speed);
	DC_Control(&Left_Top, DC_Stop, speed);	
	DC_Control(&Right_Bot, DC_Stop, speed);
	DC_Control(&Left_Bot, DC_Stop, speed);				
	break;
	case Car_right:
	DC_Control(&Right_Top, DC_Forwork, speed);
	DC_Control(&Right_Bot, DC_Forwork, speed);	
	DC_Control(&Left_Top, DC_Stop, speed);
	DC_Control(&Left_Bot, DC_Stop, speed);		
	break;
	case Car_left:
	DC_Control(&Right_Top, DC_Stop, speed);
	DC_Control(&Right_Bot, DC_Stop, speed);	
	DC_Control(&Left_Top, DC_Forwork, speed);
	DC_Control(&Left_Bot, DC_Forwork, speed);	
	break;
	case Car_move_left:
	DC_Control(&Right_Top, DC_Forwork, speed);
	DC_Control(&Left_Bot, DC_Forwork, speed);
	DC_Control(&Left_Top, DC_Back, speed);	
	DC_Control(&Right_Bot, DC_Back, speed);			
	break;
	case Car_move_right:
	DC_Control(&Right_Top, DC_Back, speed);
	DC_Control(&Left_Bot, DC_Back, speed);
	DC_Control(&Left_Top, DC_Forwork, speed);	
	DC_Control(&Right_Bot, DC_Forwork, speed);			
	break;
	case Car_dc_right_back:
	DC_Control(&Right_Top, DC_Back, speed);
	DC_Control(&Left_Bot, DC_Stop, speed);
	DC_Control(&Left_Top, DC_Stop, speed);	
	DC_Control(&Right_Bot, DC_Back, speed);			
	break;
	case Car_dc_left_back:
	DC_Control(&Right_Top, DC_Stop, speed);
	DC_Control(&Left_Bot, DC_Back, speed);
	DC_Control(&Left_Top, DC_Back, speed);	
	DC_Control(&Right_Bot, DC_Stop, speed);			
	break;
	}
};
void Car_Init(TIM_HandleTypeDef *tim ){
DC_Init(&Right_Bot,GPIOB, GPIO_PIN_3,tim, TIM_CHANNEL_3);
DC_Init(&Left_Bot,GPIOA, GPIO_PIN_6,tim, TIM_CHANNEL_2);
DC_Init(&Left_Top,GPIOA, GPIO_PIN_4,tim, TIM_CHANNEL_1);
DC_Init(&Right_Top,GPIOB, GPIO_PIN_5,tim, TIM_CHANNEL_4);
Car_control(Car_stop,0);
}
