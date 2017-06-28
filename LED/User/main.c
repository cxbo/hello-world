/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    22-November-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
	
  ///////////////////////////////////////////////////////////////////////////////https://shop192945717.taobao.com

  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define sbi(ADDRESS,BIT) 	((ADDRESS->BSRR = BIT))	// Set bit
#define cbi(ADDRESS,BIT) 	((ADDRESS->BRR = BIT))	// Clear bit
#define	bis(ADDRESS,BIT)	(GPIO_ReadInputDataBit(ADDRESS,BIT))	// Is bit set?
#define	bic(ADDRESS,BIT)	(!GPIO_ReadInputDataBit(ADDRESS,BIT))	// Is bit clear
#define	toggle(ADDRESS,BIT)	(GPIO_WriteBit(ADDRESS,BIT,(BitAction)((1-GPIO_ReadOutputDataBit(ADDRESS,BIT)))))	// Toggle bit

void Delay(uint32_t nCount)
{
  while (nCount != 0)
  {
    nCount--;
  }
}
void uart_putc(unsigned char c)
{
	while(!((USART1->ISR)&(1<<7)));
	USART1->TDR=c;	
}
void uart_puts(char *s )
{
	while (*s)
	uart_putc(*s++);
}
void GPIO_INIT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC, ENABLE);					  											 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_13;                 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void USART_INIT(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef 	NVIC_InitStructure;
	
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );						
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);     											 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;                 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);   

		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		
		USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
void SYSTICK_INIT(void)
{
		SysTick_Config(SystemCoreClock / 1000);	//Set SysTick Timer for 1ms interrupts
		//SysTick_Config(SystemCoreClock / 200);	//Set SysTick Timer for 5ms interrupts
		//SysTick_Config(SystemCoreClock / 100);	//Set SysTick Timer for 10ms interrupts
		//SysTick_Config(SystemCoreClock / 10);	//Set SysTick Timer for 100ms interrupts     
}

int main(void)
{
	SYSTICK_INIT();
	GPIO_INIT();
	USART_INIT();
	uart_puts("Fresh Persimmon all right reserved!");
  while (1)
  {
		Delay(800000);
		toggle(GPIOC,GPIO_Pin_13);
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
