
/*
 GPIO ����
*/

#include "stm32f10x.h" 

/*
��ʼ�� LED GPIOΪ�������ģʽ
��ʼPC8 ---> �������ģʽ���ߵ�ƽ

0x4001 1004

#define  PC_CRH                *(volatile unsigned int *)0x40011004

int a;
a =9;

volatile int a;

*/

#define  PC_CRH     *(volatile unsigned int *)0x40011004
	
void InitLedGpio(void)
{
	 uint32_t reg_val = 0;
	
	 //��GPIOC��ʱ��
	 RCC->APB2ENR |= (0x1<<4);
	
	 reg_val = GPIOC->CRH;  //PC8 --> �������ģʽ
	 reg_val = reg_val & 0xFFFFFFF0;
	 reg_val |= 0x3;
	
	 GPIOC->CRH = reg_val;  
	
	 GPIOC->ODR |=  0x1<<8;  //0x100
	
}

/*
 �򿪹ر�LED�� 
  0---���ر�LED��
  1---����LED��
*/
void TurnOnOff(uint8_t  onoff)
{
		if(onoff)
		{
			  //��LED��
				GPIOC->ODR  &=  ~(0x1<<8); 
		}
		else
		{
			  GPIOC->ODR |=  0x1<<8;
		}
}

/*


PC9 ��Ӧ�ĸ���ʱ�������ͨ����










 PC9
 BEEP��ʼ�� TIM3 --->CH4 ͨ��


 ��ʼ��PC9 �����������

*/

void InitBeepGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	
	RCC->APB2ENR |= 0x01; //��GPIO���ù���ʱ��
	
 //TIM3_CH4 -->PC9  TIM3_CH1-->PC6  TIM3_CH2-->PC7  TIM3_CH3-->PC8
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_9);
		
}	


/*

 ����PWM�ź�������LED�� ��ʱ��

 PC6--->BLUE
 PC7--->GREEN
 PC8 ---> RED

 ��ʼ�� PC6��PC7 ,PC8 ΪTIME3�����ͨ��
*/

void InitPwmLedGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	
	RCC->APB2ENR |= 0x01; //��GPIO���ù���ʱ��
	
 //TIM3_CH4 -->PC9  TIM3_CH1-->PC6  TIM3_CH2-->PC7  TIM3_CH3-->PC8
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
}








 
                     





