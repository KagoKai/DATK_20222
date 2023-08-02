#include "Dong_co.h"

void pwm_set_duty(TIM_HandleTypeDef *tim, uint32_t chanel,uint8_t duty)
{
	uint16_t ccr = (uint16_t)duty*(tim->Instance->ARR)/100;
	switch(chanel)
	{
		case TIM_CHANNEL_1:
			tim->Instance->CCR1 = ccr;
			break;
		case TIM_CHANNEL_2:
			tim->Instance->CCR2 = ccr;
			break;
		case TIM_CHANNEL_3:
			tim->Instance->CCR3 = ccr;
			break;
		case TIM_CHANNEL_4:
			tim->Instance->CCR4 = ccr;
			break;
	}
}
void motor_control(Motor_Typedef *motor, MotorState state, uint8_t speed)
{
	switch(state)
	{
		case MOTOR_STOP:
			HAL_GPIO_WritePin(motor->io_port, motor->io_pin, GPIO_PIN_RESET);
			pwm_set_duty(motor->tim, motor->tim_chanel , 0);
			break;
		case MOTOR_CW:
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,GPIO_PIN_RESET);
			pwm_set_duty(motor->tim, motor->tim_chanel,speed);
			break;
		case MOTOR_CCW:
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,GPIO_PIN_SET);
			pwm_set_duty(motor->tim,motor->tim_chanel,100 - speed);
			break;
	}
}
void motor_init(Motor_Typedef *motor, GPIO_TypeDef *io_port,
								uint16_t io_pin,TIM_HandleTypeDef *tim, uint32_t tim_chanel)
{
	motor->io_port = io_port;
	motor->io_pin = io_pin;
	motor->tim = tim;
	motor->tim_chanel = tim_chanel;
	HAL_TIM_PWM_Start(motor->tim, motor->tim_chanel);
}
