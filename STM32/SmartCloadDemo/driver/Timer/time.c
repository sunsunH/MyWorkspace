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
	
	/*  TIM3 中断嵌套设计*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_Config(void)
{
	/* -----------------------------------------------------------------------
    TIM3 配置: 输出比较时序模式:
    
    本试验中 TIM3输入时钟(TIM3CLK) 被设为APB1 时钟 (PCLK1),  
      => TIM3CLK = PCLK1 = SystemCoreClock = 48 MHz
          
    当 TIM3 计数时钟 设为1 MHz, 预分频器可以按照下面公式计算：
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = (PCLK1 /1 MHz) - 1
  ----------------------------------------------------------------------- */   

  /* 计算预分频值  ,设置TIM3计数时钟 1MHZ */
  PrescalerValue = (uint16_t) (SystemCoreClock  / 1000000) - 1;

	/* Time 定时器基础设置 */
	TIM_TimeBaseStructure.TIM_Period = 1000; //设置定时时间为1000us
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* 预分频器配置 */
	TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   /* TIM3 更新中断使能 */
	
	TIM_Cmd(TIM3, ENABLE);    /* TIM3 使能 */
}

	//TIM2 初始化
	
void TIM2_Config(void)
{
	 //启用TIMER2时钟
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* -----------------------------------------------------------------------
    TIM2 配置: 
    
    本试验中 TIM2输入时钟(TIM2CLK) 被设为APB1 时钟 (PCLK1),  
      => TIM2CLK = PCLK1 = SystemCoreClock = 48 MHz
          
    当 TIM2 计数时钟 设为1 MHz, 预分频器可以按照下面公式计算：
       Prescaler = (TIM2CLK / TIM3 counter clock) - 1
       Prescaler = (PCLK1 /1 MHz) - 1
                                                  
  ----------------------------------------------------------------------- */   

  /* 计算预分频值  ,设置TIM3计数时钟 1MHZ */
  PrescalerValue = (uint16_t) (SystemCoreClock  / 1000000) - 1;

  /* Time 定时器基础设置 */
  TIM_TimeBaseStructure.TIM_Period = 0xfffffffe; 
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* 预分频器配置 */
  TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);

  
  /* TIM2 禁止更新中断 */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  /* TIM2 使能 */
  TIM_Cmd(TIM2, ENABLE);
	
	}


	//延时时间
	void Delay_us(uint32_t delay_time)
	{
		uint32_t  cntvalue = 0;
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE); //启动定时器2
		
		do
		{
			 cntvalue = TIM2->CNT;
						
		}while(cntvalue < delay_time);
		
	}
	

