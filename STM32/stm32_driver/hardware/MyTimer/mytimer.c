
/*
  Timer2 驱动
*/

#include "stm32f10x.h"
#include "misc.h"

/*
 1) 打开定时器时钟
 2) 设置定时器2的工作方式
 3) 设置分频系数
 4) 允许定时器中断
 5) 设置定时器中断优先级
 6) 启动定时器
 
 根据定时时间
 如何来计算定时器的初值:
 
 已知定时器的工作时钟频率: APB1_CLK * 2 = 72MHZ
 
 PSC ---> 71
 
 计数脉冲频率 = 72/(71+1) = 1MHz
 

 希望定时时间 ---> 1ms
 
 确定定时器的计数脉冲频率，1MHz
 

*/
void InitMyTimer2(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//允许TIMER2时钟
	RCC->APB1ENR |= 0x1;
	
	TIM2->CR1 |= (0x1<<2); //设置只有计数溢出才产生中断
	TIM2->CR1 &=  ~(0x3<<5); //设置定时器的工作方式为边沿对齐方式
	TIM2->CR1 &= (~0x1); //关闭定时器
	TIM2->CR1 &=  ~(0x3<<3);//设置定时器为向上计数，周期工作模式
	
	TIM2->PSC = 71; //计数脉冲频率 = 72/(71+1) = 1MHz
	TIM2->DIER |= 0x1; //允许定时器更新中断
	
	TIM2->ARR = 1000; //定时时间1000us -->1ms
	
	
	
	/* Configure the Priority Grouping with 1 bit */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM2->CR1 |= 0x1; //启动定时器2
	
	
}


/*
 初始化TIMER3
*/

void InitMyTimer3(void)
{

	//允许TIMER3时钟
	RCC->APB1ENR |= 0x1<<1;
	
	TIM3->CR1 |= (0x1<<2); //设置只有计数溢出才产生中断
	TIM3->CR1 &=  ~(0x3<<5); //设置定时器的工作方式为边沿对齐方式
	TIM3->CR1 &= (~0x1); //关闭定时器
	TIM3->CR1 &=  ~(0x3<<3);//设置定时器为向上计数，周期工作模式
	
	TIM3->PSC = 71; //计数脉冲频率 = 72/(71+1) = 1MHz
	TIM3->DIER &= ~0x1; //禁止定时器更新中断
	//TIM3->DIER |= 0x1; 
	
	//设置TIM3_CH4 位PWM1输出模式
	TIM3->CCER  &= ~(0x1<<12);
	TIM3->CCMR2 &= 0xff;
	TIM3->CCMR2 |= (0x60<<8);
//	TIM3->CCER  |= (0x1<<12); //使能输出 禁止第4个通道输出
	
	//设置 TIM3_CH1，TIM3_CH2，TIM3_CH3 都设置为PWM1输出模式
	
	TIM3->CCER  &= (~0xfff); 
	
	TIM3->CCMR1 = 0x6060;
	TIM3->CCMR2 &= 0xff00;
	TIM3->CCMR2 |= 0x60;
	
	TIM3->CCER  |= 0x333; //允许输出PWM信号，低电平有效
	
	

	TIM3->ARR = 1000; //定时时间1000us -->1ms，周期为  10KHZ PWM信号
	TIM3->CCR4 = 500;
	
  TIM3->CCR1 = 0;    //蓝色
	TIM3->CCR2 = 0;   //绿色
	TIM3->CCR3 = 0;  //红色
	
	TIM3->CR1 |= 0x1; //启动定时器3
}


void setRGBPwmWidth(uint16_t blueWidth, uint16_t greenWidth, uint16_t redWidth)
{
	  TIM3->CCR1 = blueWidth;
		TIM3->CCR2 = greenWidth;
		TIM3->CCR3 = redWidth;
}





