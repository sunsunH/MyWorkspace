#include "time.h"
#include "Led.h"


uint16_t PrescalerValue = 0;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;


void TIM3_INT_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/*  TIM3 �ж�Ƕ�����*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_Config(void)
{
	/* -----------------------------------------------------------------------
    TIM3 ����: ����Ƚ�ʱ��ģʽ:
    
    �������� TIM3����ʱ��(TIM3CLK) ����ΪAPB1 ʱ�� (PCLK1),  
      => TIM3CLK = PCLK1 = SystemCoreClock = 48 MHz
          
    �� TIM3 ����ʱ�� ��Ϊ1 MHz, Ԥ��Ƶ�����԰������湫ʽ���㣺
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = (PCLK1 /1 MHz) - 1
  ----------------------------------------------------------------------- */   

  /* ����Ԥ��Ƶֵ  ,����TIM3����ʱ�� 1MHZ */
  PrescalerValue = (uint16_t) (SystemCoreClock  / 1000000) - 1;

	/* Time ��ʱ���������� */
	TIM_TimeBaseStructure.TIM_Period = 1000; //���ö�ʱʱ��Ϊ1000us
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* Ԥ��Ƶ������ */
	TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   /* TIM3 �����ж�ʹ�� */
	
	TIM_Cmd(TIM3, ENABLE);    /* TIM3 ʹ�� */
}

	//TIM2 ��ʼ��
	
void TIM2_Config(void)
{
	 //����TIMER2ʱ��
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* -----------------------------------------------------------------------
    TIM2 ����: 
    
    �������� TIM2����ʱ��(TIM2CLK) ����ΪAPB1 ʱ�� (PCLK1),  
      => TIM2CLK = PCLK1 = SystemCoreClock = 48 MHz
          
    �� TIM2 ����ʱ�� ��Ϊ1 MHz, Ԥ��Ƶ�����԰������湫ʽ���㣺
       Prescaler = (TIM2CLK / TIM3 counter clock) - 1
       Prescaler = (PCLK1 /1 MHz) - 1
                                                  
  ----------------------------------------------------------------------- */   

  /* ����Ԥ��Ƶֵ  ,����TIM3����ʱ�� 1MHZ */
  PrescalerValue = (uint16_t) (SystemCoreClock  / 1000000) - 1;

  /* Time ��ʱ���������� */
  TIM_TimeBaseStructure.TIM_Period = 0xfffffffe; 
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Ԥ��Ƶ������ */
  TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);

  
  /* TIM2 ��ֹ�����ж� */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  /* TIM2 ʹ�� */
  TIM_Cmd(TIM2, ENABLE);
	
	}


	//��ʱʱ��
	void Delay_us(uint32_t delay_time)
	{
		uint32_t  cntvalue = 0;
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE); //������ʱ��2
		
		do
		{
			 cntvalue = TIM2->CNT;
						
		}while(cntvalue < delay_time);
		
	}
	

