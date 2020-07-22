#include "Sysclock.h"

void HSE_System_Clock_Init()
{
	RCC_DeInit();						//RCC时钟源取消现有设置
	RCC_HSEConfig(RCC_HSE_ON);			//开启外部HSE高精度时钟

	__IO uint32_t HSE_Start_Status = 0;	//HSE开启结果状态缓存

	HSE_Start_Status = RCC_WaitForHSEStartUp();//等待HSE正式开启
	if (HSE_Start_Status == SUCCESS)		//如果开启成功再进行下一步配置
	{
		//指令预取使能，加快指令执行速度
		//
		FLASH_PrefetchBufferCmd(ENABLE);
		FLASH_SetLatency(FLASH_Latency_2);

		//各个部分分频配置
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);

		//配置PLL锁相环时钟来源是HSE，9倍频(72MHz)
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		//RCC使能
		RCC_PLLCmd(ENABLE);
		//等待PLL稳定
		while (RCC_FLAG_PLLRDY == RESET);
		//设定系统时钟是PLL锁相环
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		//等待设置成功
		while (RCC_GetSYSCLKSource() != 0x08);
	}
	else
	{
		//如果无法开启HSE，停止运行程序
		while (1);
	}

}
