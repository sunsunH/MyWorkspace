#include "stm32f0xx.h"
#include "SysTick.h"
#include "time.h"
#include "stdio.h"
#include "DHT11.h"
/************************************************************
��������DHT11_Rst
���ܣ� ��λDHT11
�����������
�����������
����ֵ����

��ע�� ��

GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

************************************************************/
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT

	GPIO_ResetBits(GPIOB,GPIO_Pin_8);

    delay_ms(20);    	//��������18ms

	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	delay_us(30);     	//��������20~40us
}

/************************************************************
��������DHT11_Check
���ܣ� ����Ƿ����DHT11
�����������
�����������
����ֵ��0: DHT11����  1��DHT11������

��ע�� ��

************************************************************/
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
  	while (DHT11_DQ_IN&&retry<100)//DHT11������40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
/************************************************************
��������DHT11_Read_Bit
���ܣ� ����һ��λֵ
�����������
�����������
����ֵ��0:��ȡ��λֵΪ0 1����ȡ��λֵΪ1

��ע�� ��

************************************************************/
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
/************************************************************
��������DHT11_Read_Byte
���ܣ� ����һ���ֽ�
�����������
�����������
����ֵ���������ֽ�ֵ

��ע�� ��

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
��������DHT11_Read_Data
���ܣ� ����һ���ֽ�
���������temp�� humi
���������temp���¶�ֵ  humi��ʪ��ֵ
����ֵ��0����ȡ���ݳɹ�  1����ȡ����ʧ��

��ע�� ��

************************************************************/
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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
��������DHT11_Init
���ܣ� ��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
�����������
�����������
����ֵ��0������  1��������

��ע�� ��

//����PB8 λ�������ģʽ

************************************************************/	 
u8 DHT11_Init(void)
{
	//��ʼ��PORTBΪ���״̬
	GPIO_InitTypeDef GPIO_InitStructure;
	
		//ʹ��PORTBʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //�����������ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	

	DHT11_Rst();
	return DHT11_Check();
}

