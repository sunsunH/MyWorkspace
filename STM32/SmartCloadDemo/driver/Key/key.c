#include "key.h"


//KEY --- PA8

void EXIT_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

  	/* config the extiline(PA8) clock and AFIO clock */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
	/* Configyre P[A|B|C|D|E]0  NIVC  */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

  	/* EXTI line gpio config(PA8) */	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; 
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* EXTI line(PA8) mode config */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);
	EXTI_InitStruct.EXTI_Line = EXTI_Line8;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿中断
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct); 
}
