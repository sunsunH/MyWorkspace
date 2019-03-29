/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
#include "usart_driver.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	
}

//外部中断0 中断服务处理程序
void EXTI0_IRQHandler(void)
{
		if(EXTI_GetFlagStatus(EXTI_Line0))
		{
			 //产生了外部中断 0
			 printf("key1 interrupt OK!\r\n");
		}
		
		EXTI_ClearFlag(EXTI_Line0); //清除外部中断0的中断标志
}

void EXTI2_IRQHandler(void)
{
	
}

void EXTI4_IRQHandler(void)
{

}

//extern IIC_Type_Def IIC_Structure;
void EXTI9_5_IRQHandler(void)
{
}

void EXTI15_10_IRQHandler(void)
{
	
}




/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).  
串口1中断服务处理程序里面，就来接收数据
*/
/******************************************************************************/

//定义UART1的接收缓冲区
uint8_t uart1Buf[128] ={0};
uint8_t uart1RecvLen = 0; //保存串口1接收到的数据的长度


void USART1_IRQHandler(void)
{
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			  //UART1 接收到了数据
				uart1Buf[uart1RecvLen] = usart1_getc();
			  uart1RecvLen++;
			
				//清除中断标志
			  USART_ClearITPendingBit (USART1, USART_IT_RXNE);	
		}
}


//定义UART3的接收缓冲区
uint8_t uart3Buf[128] ={0};
uint8_t uart3RecvLen = 0; //保存串口3接收到的数据的长度
void USART3_IRQHandler(void)
{
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
		{
			
				//UART3 接收到了数据
				uart3Buf[uart3RecvLen] = usart3_getc();
			  uart3RecvLen++;
				//串口接收到数据
				USART_ClearITPendingBit (USART3, USART_IT_RXNE);	
		}

}


//TIMER2 中断服务处理程序

uint32_t timer2_cnt = 0;
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0x1)
	{
		timer2_cnt++;
		if(timer2_cnt % 1000 ==0)
		{
			printf("Timer2 Interrupt OK\r\n");
		}
		 TIM2->SR = 0x0;
	}
}



void RTCAlarm_IRQHandler(void)
{	

}




void RTC_IRQHandler(void)
{
	
}


uint32_t timer3_cnt = 0;
void TIM3_IRQHandler(void)
{	
	if(TIM3->SR&0x1)
	{
		timer3_cnt++;
		if(timer3_cnt % 1000 ==0)
		{
			printf("Timer3 Interrupt OK\r\n");
		}
		 TIM3->SR = 0x0;
	}
}


void SPI1_IRQHandler(void)
{
	
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
