#include "bsp_usart.h"

void WIFI_USART_CFG()
{
	GPIO_InitTypeDef GPIO_S;
	USART_InitTypeDef USART_S;
	
	WIFI_USART_GPIO_APBxClkCmd(WIFI_USART_GPIO_CLK,ENABLE);
	WIFI_USART_APBxClkCmd(WIFI_USART_CLK,ENABLE);
	
	GPIO_S.GPIO_Pin=WIFI_USART_TX_GPIO_PIN;
	GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(WIFI_USART_TX_GPIO_PORT,&GPIO_S);
	
	GPIO_S.GPIO_Pin=WIFI_USART_RX_GPIO_PIN;
	GPIO_S.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(WIFI_USART_RX_GPIO_PORT,&GPIO_S);
	
	
	USART_S.USART_BaudRate=WIFI_USART_BAUDRATE;
	USART_S.USART_WordLength=USART_WordLength_8b;
	USART_S.USART_StopBits=USART_StopBits_1;
	USART_S.USART_Parity=USART_Parity_No;
	USART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_S.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(WIFI_USARTx,&USART_S);
	WIFI_NVIC_CFG();		//串口中断初始化	
	USART_ITConfig(WIFI_USARTx,USART_IT_RXNE,ENABLE);
	USART_Cmd(WIFI_USARTx,ENABLE);
	
}
void WIFI_NVIC_CFG()
{
	NVIC_InitTypeDef WIFI_NVIC;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	WIFI_NVIC.NVIC_IRQChannel = WIFI_USART_IRQ;
	WIFI_NVIC.NVIC_IRQChannelPreemptionPriority = 1;
	WIFI_NVIC.NVIC_IRQChannelSubPriority = 0;
	WIFI_NVIC.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&WIFI_NVIC);

}
void EXTERN_USART_CFG()
{
	GPIO_InitTypeDef GPIO_S;
	USART_InitTypeDef USART_S;
	
	EXTERN_USART_GPIO_APBxClkCmd(EXTERN_USART_GPIO_CLK,ENABLE);
	EXTERN_USART_APBxClkCmd(EXTERN_USART_CLK,ENABLE);
	
	GPIO_S.GPIO_Pin=EXTERN_USART_TX_GPIO_PIN;
	GPIO_S.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(EXTERN_USART_TX_GPIO_PORT,&GPIO_S);
	
	GPIO_S.GPIO_Pin=EXTERN_USART_RX_GPIO_PIN;
	GPIO_S.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(EXTERN_USART_RX_GPIO_PORT,&GPIO_S);
	
	USART_S.USART_BaudRate=EXTERN_USART_BAUDRATE;
	USART_S.USART_WordLength=USART_WordLength_8b;
	USART_S.USART_StopBits=USART_StopBits_1;
	USART_S.USART_Parity=USART_Parity_No;
	USART_S.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_S.USART_Mode=USART_Mode_Tx;
	
	USART_Init(EXTERN_USARTx,&USART_S);
	USART_ITConfig(EXTERN_USARTx,USART_IT_RXNE,ENABLE);
	USART_Cmd(EXTERN_USARTx,ENABLE);
}
void EXTERN_NVIC_CFG()
{
	NVIC_InitTypeDef EXTERN_NVIC;
	EXTERN_NVIC.NVIC_IRQChannel = EXTERN_USART_IRQ;
	EXTERN_NVIC.NVIC_IRQChannelPreemptionPriority = 1;
	EXTERN_NVIC.NVIC_IRQChannelSubPriority = 1;
	EXTERN_NVIC.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&EXTERN_NVIC);

}

void Usart_SendByte(USART_TypeDef *pUx,uint8_t ch)
{
	USART_SendData(pUx,ch);
	while(USART_GetFlagStatus(pUx,USART_FLAG_TXE)==RESET);
}
void Usart_SendString(USART_TypeDef *pUx,const char * Str)
{
	for(int i=0;Str[i]!='\0';i++)
	{
		Usart_SendByte(pUx,Str[i]);
	}
while(USART_GetFlagStatus(pUx,USART_FLAG_TXE)==RESET);
}

void Usart_SendUint32(USART_TypeDef *pUx,uint32_t number)
{
	  if(number==0)
		{
			Usart_SendByte(pUx,'0');
			Usart_SendByte(pUx,'\n');
			return;
		}
		else
		{
			uint32_t number_limit = 1;
			uint8_t number_number = 0;		//数据位数
			while (number_limit < number)
			{
				number_limit *= 10;
				number_number++;
			}
			
			char number_string[10];
			number_string[number_number] = '\n';
			number_string[number_number+1] = '\0';
			for (uint8_t i = 0; i < number_number; i++)
			{
				number_string[number_number - i - 1] =(char)( number % 10+'0'-0);
				number /= 10;
			}
			Usart_SendString(pUx,number_string);
		}
}
