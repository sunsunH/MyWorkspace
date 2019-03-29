
//STM32 F051 LED driver

#include "led.h"

/*
 
 LED4  -- PB0
 LED3  -- PB1
 LED2  -- PB2
 
 RELAY -- PB7

*/

void initLedGpio(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	
	//����GPIOB�˿�ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
  	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_7 ;
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_Level_3;
  	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//��λ��Ӧ��BIT,��ʼ��Ϩ��LED��
	GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_7);

}


/*
  ����  Ϩ�� LED��

  onOff��
    0 --- Ϩ��  LED��
    1 --- ����  LED��
*/

void turnOnOffLed(uint8_t onOff)
{
	if(onOff == 0)
	{
	 	GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_7);
	}
	else if(onOff == 1)
	{
	 	GPIO_ResetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_7);
	}
	 
}

