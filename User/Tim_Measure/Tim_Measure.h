#ifndef TIM_MEASURE_H_
#define TIM_MEASURE_H_

#include "stm32f10x.h"

void TIM_NVIC_Init();		//定时器中断初始化
void TIM_GPIO_Init();		//定时器输入引脚初始化
void TIM_Mode_Init();		//定时器初始化
void TIM_IC_Mode_Init();	//定时器输入模式初始化

void TIM_General_Init();	//定时器全局初始化




#endif // !TIM_MEASURE_H_
