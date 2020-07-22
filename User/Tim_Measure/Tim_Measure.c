#include "Tim_Measure.h"

void TIM_NVIC_Init()
{
	
	NVIC_InitTypeDef TIM_Structure;

	TIM_Structure.NVIC_IRQChannel = TIM2_IRQn;
	TIM_Structure.NVIC_IRQChannelCmd = ENABLE;
	TIM_Structure.NVIC_IRQChannelPreemptionPriority = 0;
	TIM_Structure.NVIC_IRQChannelSubPriority = 3;

	NVIC_Init(&TIM_Structure);

}

void TIM_GPIO_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef TIM_Structure;
	TIM_Structure.GPIO_Mode = GPIO_Mode_IPD;
	TIM_Structure.GPIO_Pin = GPIO_Pin_0;

	GPIO_Init(GPIOA,&TIM_Structure);
}

void TIM_Mode_Init()
{
	TIM_TimeBaseInitTypeDef TIM_Structure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Structure.TIM_Period =  2000- 1;							//1S产生一个溢出中断
	TIM_Structure.TIM_Prescaler = 36000-1;						//分频后得到的时钟频率是10KHz
	TIM_Structure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_Structure);

}

void TIM_IC_Mode_Init()
{
	TIM_ICInitTypeDef TIM_Structure;
	TIM_Structure.TIM_Channel = TIM_Channel_1;
	TIM_Structure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_Structure.TIM_ICPrescaler =TIM_ICPSC_DIV1;						//每1次上升沿引发一次频率技术
	TIM_Structure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_Structure.TIM_ICFilter = 0;

	TIM_ICInit(TIM2, &TIM_Structure);
}

void TIM_General_Init()
{
	TIM_GPIO_Init();
	TIM_NVIC_Init();
	TIM_Mode_Init();
	TIM_IC_Mode_Init();
	TIM_ClearFlag(TIM2,TIM_FLAG_CC1|TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE);	//溢出中断、跳变中断使能
	TIM_Cmd(TIM2, ENABLE);				//测量定时器启动
	
}
