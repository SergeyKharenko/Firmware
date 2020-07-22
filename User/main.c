#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "Sysclock.h"
#include "Tim_Measure.h"
#include "bsp_usart.h"
#include "Wifi.h"

extern uint8_t measure_mode;
extern uint32_t frequency;
extern struct Cache_Container Wifi_Cache;
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_S;
	
	GPIO_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_S.GPIO_Pin=GPIO_Pin_1;
	GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_S);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	
	HSE_System_Clock_Init();
	Wifi_Cache = Cache_Init_Get();
	if(Wifi_Init()!=NO_ERROR)
		return 0;
	//Lan_Init();
	while (!Wifi_Client_Connected());
	Wifi_Get_Client_IP();
	while(Wifi_TCP_Setup() != NO_ERROR);
	if (Wifi_Direct_CMD(true) != NO_ERROR)
		return 0;

	//EXTERN_USART_CFG();
	TIM_General_Init();
	measure_mode = 1;				//置位开始测量
	while (1)
	{
		if (measure_mode == 0)
		{
			TIM_Cmd(TIM2, DISABLE);		//关闭定时器，防止带来无效值
			//Usart_SendUint32(EXTERN_USARTx, frequency);	//输出频率
			//Lan_TCP_Run(frequency);					//以太网输出
			Wifi_Send(NULL, frequency, true);
			frequency = 0;				//频率值恢复0
			measure_mode = 1;
			//Lan_UDP_Broadcast();
			TIM_Cmd(TIM2, ENABLE);
		}
		
	}
}

