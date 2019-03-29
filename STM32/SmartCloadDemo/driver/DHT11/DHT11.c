#include "stm32f0xx.h"
#include "SysTick.h"
#include "time.h"
#include "stdio.h"
#include "DHT11.h"
/************************************************************
函数名：DHT11_Rst
功能： 复位DHT11
输入参数：无
输出参数：无
返回值：无

备注： 无

GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

************************************************************/
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT

	GPIO_ResetBits(GPIOB,GPIO_Pin_8);

    delay_ms(20);    	//拉低至少18ms

	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	delay_us(30);     	//主机拉高20~40us
}

/************************************************************
函数名：DHT11_Check
功能： 检测是否存在DHT11
输入参数：无
输出参数：无
返回值：0: DHT11存在  1：DHT11不存在

备注： 无

************************************************************/
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
  	while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
/************************************************************
函数名：DHT11_Read_Bit
功能： 读出一个位值
输入参数：无
输出参数：无
返回值：0:读取该位值为0 1：读取该位值为1

备注： 无

************************************************************/
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
/************************************************************
函数名：DHT11_Read_Byte
功能： 读出一个字节
输入参数：无
输出参数：无
返回值：读到的字节值

备注： 无

************************************************************/
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
/************************************************************
函数名：DHT11_Read_Data
功能： 读出一个字节
输入参数：temp， humi
输出参数：temp：温度值  humi：湿度值
返回值：0：读取数据成功  1：读取数据失败

备注： 无

************************************************************/
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}
/************************************************************
函数名：DHT11_Init
功能： 初始化DHT11的IO口 DQ 同时检测DHT11的存在
输入参数：无
输出参数：无
返回值：0：存在  1：不存在

备注： 无

//设置PB8 位输出工作模式

************************************************************/	 
u8 DHT11_Init(void)
{
	//初始化PORTB为输出状态
	GPIO_InitTypeDef GPIO_InitStructure;
	
		//使能PORTB时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //推挽输出工作模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	

	DHT11_Rst();
	return DHT11_Check();
}

