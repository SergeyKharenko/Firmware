#ifndef BSP_USART_H_
#define BSP_USART_H_

#include "stm32f10x.h"
#include "stdio.h"


//####################  WIFI 串口设置  ##################################

#define  WIFI_USARTx                   USART1
#define  WIFI_USART_CLK                RCC_APB2Periph_USART1
#define  WIFI_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  WIFI_USART_BAUDRATE           115200

// USART GPIO ?????
#define  WIFI_USART_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  WIFI_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  WIFI_USART_TX_GPIO_PORT       GPIOA   
#define  WIFI_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  WIFI_USART_RX_GPIO_PORT       GPIOA
#define  WIFI_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  WIFI_USART_IRQ                USART1_IRQn
#define  WIFI_USART_IRQHandler         USART1_IRQHandler

//####################  外接串口设置    #######################################

#define  EXTERN_USARTx                   USART2
#define  EXTERN_USART_CLK                RCC_APB1Periph_USART2
#define  EXTERN_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  EXTERN_USART_BAUDRATE           115200

// USART GPIO ?????
#define  EXTERN_USART_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  EXTERN_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  EXTERN_USART_TX_GPIO_PORT       GPIOA   
#define  EXTERN_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  EXTERN_USART_RX_GPIO_PORT       GPIOA
#define  EXTERN_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  EXTERN_USART_IRQ                USART2_IRQn
#define  EXTERN_USART_IRQHandler         USART2_IRQHandler


void WIFI_USART_CFG();
void WIFI_NVIC_CFG();

void EXTERN_USART_CFG();
void EXTERN_NVIC_CFG();

void Usart_SendString(USART_TypeDef *pUx,const char * Str);
void Usart_SendByte(USART_TypeDef *pUx,uint8_t ch);
void Usart_SendUint32(USART_TypeDef *pUx,uint32_t number);

#endif

