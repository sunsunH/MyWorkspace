
/*
  Timer2 ����
*/

#include "stm32f10x.h"
#include "misc.h"

/*
 1) �򿪶�ʱ��ʱ��
 2) ���ö�ʱ��2�Ĺ�����ʽ
 3) ���÷�Ƶϵ��
 4) ����ʱ���ж�
 5) ���ö�ʱ���ж����ȼ�
 6) ������ʱ��
 
 ���ݶ�ʱʱ��
 ��������㶨ʱ���ĳ�ֵ:
 
 ��֪��ʱ���Ĺ���ʱ��Ƶ��: APB1_CLK * 2 = 72MHZ
 
 PSC ---> 71
 
 ��������Ƶ�� = 72/(71+1) = 1MHz
 

 ϣ����ʱʱ�� ---> 1ms
 
 ȷ����ʱ���ļ�������Ƶ�ʣ�1MHz
 

*/
void InitMyTimer2(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//����TIMER2ʱ��
	RCC->APB1ENR |= 0x1;
	
	TIM2->CR1 |= (0x1<<2); //����ֻ�м�������Ų����ж�
	TIM2->CR1 &=  ~(0x3<<5); //���ö�ʱ���Ĺ�����ʽΪ���ض��뷽ʽ
	TIM2->CR1 &= (~0x1); //�رն�ʱ��
	TIM2->CR1 &=  ~(0x3<<3);//���ö�ʱ��Ϊ���ϼ��������ڹ���ģʽ
	
	TIM2->PSC = 71; //��������Ƶ�� = 72/(71+1) = 1MHz
	TIM2->DIER |= 0x1; //����ʱ�������ж�
	
	TIM2->ARR = 1000; //��ʱʱ��1000us -->1ms
	
	
	
	/* Configure the Priority Grouping with 1 bit */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM2->CR1 |= 0x1; //������ʱ��2
	
	
}


/*
 ��ʼ��TIMER3
*/

void InitMyTimer3(void)
{

	//����TIMER3ʱ��
	RCC->APB1ENR |= 0x1<<1;
	
	TIM3->CR1 |= (0x1<<2); //����ֻ�м�������Ų����ж�
	TIM3->CR1 &=  ~(0x3<<5); //���ö�ʱ���Ĺ�����ʽΪ���ض��뷽ʽ
	TIM3->CR1 &= (~0x1); //�رն�ʱ��
	TIM3->CR1 &=  ~(0x3<<3);//���ö�ʱ��Ϊ���ϼ��������ڹ���ģʽ
	
	TIM3->PSC = 71; //��������Ƶ�� = 72/(71+1) = 1MHz
	TIM3->DIER &= ~0x1; //��ֹ��ʱ�������ж�
	//TIM3->DIER |= 0x1; 
	
	//����TIM3_CH4 λPWM1���ģʽ
	TIM3->CCER  &= ~(0x1<<12);
	TIM3->CCMR2 &= 0xff;
	TIM3->CCMR2 |= (0x60<<8);
//	TIM3->CCER  |= (0x1<<12); //ʹ����� ��ֹ��4��ͨ�����
	
	//���� TIM3_CH1��TIM3_CH2��TIM3_CH3 ������ΪPWM1���ģʽ
	
	TIM3->CCER  &= (~0xfff); 
	
	TIM3->CCMR1 = 0x6060;
	TIM3->CCMR2 &= 0xff00;
	TIM3->CCMR2 |= 0x60;
	
	TIM3->CCER  |= 0x333; //�������PWM�źţ��͵�ƽ��Ч
	
	

	TIM3->ARR = 1000; //��ʱʱ��1000us -->1ms������Ϊ  10KHZ PWM�ź�
	TIM3->CCR4 = 500;
	
  TIM3->CCR1 = 0;    //��ɫ
	TIM3->CCR2 = 0;   //��ɫ
	TIM3->CCR3 = 0;  //��ɫ
	
	TIM3->CR1 |= 0x1; //������ʱ��3
}


void setRGBPwmWidth(uint16_t blueWidth, uint16_t greenWidth, uint16_t redWidth)
{
	  TIM3->CCR1 = blueWidth;
		TIM3->CCR2 = greenWidth;
		TIM3->CCR3 = redWidth;
}





