

/*
 �ⲿ�ж� 0 �����жϳ���
 
 K1 ---> PA0 ---��EXTI0
 
*/

#include "stm32f10x.h" 
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stdio.h"

/*
 1) �� PA0 ��ʱ��
 2) ����PA0 �Ĺ���ģʽ ��������ģʽ
 
 3) �����ⲿ�ж�0�������ź���---��PA0
 
 4) �����ⲿ�ж�0
 5) �����ⲿ�ж�0�Ĵ����ź�Ϊ �½��ش���
 
 6) ��ʼ�������жϿ������������ⲿ�ж�0�������ⲿ�ж�0�����ȼ�

*/
void InitKey1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// �� PA ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	/* Configure all the GPIOA in Input pull-up mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	/* Selects PA.0 as EXTI Line 0 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	/* Enables external lines0 interrupt generation on falling edge */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	/* Enable EXTI4 interrupt with Preemption Priority 1 and Sub Priority as 7 */

/* Configure the Priority Grouping with 1 bit */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}







