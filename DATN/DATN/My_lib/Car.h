#ifndef CAR_H
#define CAR_H
#include "stm32f1xx.h"
#include "Dong_co.h"
typedef enum{
Car_forwork,
Car_back,
Car_stop,
Car_right,
Car_left,
Car_move_right,
Car_move_left,
Car_dc_right_back,  // di 2 banh phai xuong
Car_dc_left_back,   // di 2 banh trai xuong
} Car_Status;

typedef enum{
Car_go_forward,
Car_go_right,
Car_go_back,
Car_go_left,
} Car_go_status;

void Car_Init(TIM_HandleTypeDef *tim );
void Car_control(Car_Status car_status ,uint8_t speed);

#endif
