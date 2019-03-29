
/*
 GPIO 驱动
*/

#include "stm32f10x.h" 

/*
初始化 LED GPIO为推挽输出模式
初始PC8 ---> 推挽输出模式，高电平

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
	
	 //打开GPIOC的时钟
	 RCC->APB2ENR |= (0x1<<4);
	
	 reg_val = GPIOC->CRH;  //PC8 --> 推挽输出模式
	 reg_val = reg_val & 0xFFFFFFF0;
	 reg_val |= 0x3;
	
	 GPIOC->CRH = reg_val;  
	
	 GPIOC->ODR |=  0x1<<8;  //0x100
	
}

/*
 打开关闭LED灯 
  0---》关闭LED灯
  1---》打开LED灯
*/
void TurnOnOff(uint8_t  onoff)
{
		if(onoff)
		{
			  //打开LED灯
				GPIOC->ODR  &=  ~(0x1<<8); 
		}
		else
		{
			  GPIOC->ODR |=  0x1<<8;
		}
}

/*


PC9 对应哪个定时器的输出通道？










 PC9
 BEEP初始化 TIM3 --->CH4 通道


 初始化PC9 复用推挽输出

*/

void InitBeepGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	
	RCC->APB2ENR |= 0x01; //打开GPIO复用功能时钟
	
 //TIM3_CH4 -->PC9  TIM3_CH1-->PC6  TIM3_CH2-->PC7  TIM3_CH3-->PC8
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_9);
		
}	


/*

 产生PWM信号来控制LED灯 定时器

 PC6--->BLUE
 PC7--->GREEN
 PC8 ---> RED

 初始化 PC6，PC7 ,PC8 为TIME3的输出通道
*/

void InitPwmLedGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	
	RCC->APB2ENR |= 0x01; //打开GPIO复用功能时钟
	
 //TIM3_CH4 -->PC9  TIM3_CH1-->PC6  TIM3_CH2-->PC7  TIM3_CH3-->PC8
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
}








 
                     





