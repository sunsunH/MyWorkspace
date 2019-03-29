
/*
	main.c
*/

#include "sys_rcc.h"
#include "usart_driver.h"
#include "SysTick.h"
#include <string.h>

void InitLedGpio(void);
void TurnOnOff(uint8_t  onoff);
void InitKey1(void);

void InitMyTimer2(void);



void InitMyTimer3(void);
void InitBeepGpio(void);
void InitPwmLedGpio(void);

int SendBleATCmd(char *atCmd);
uint8_t  CalCRC(uint8_t *buf, uint8_t len);
void setRGBPwmWidth(uint16_t blueWidth, uint16_t greenWidth, uint16_t redWidth);


int count = 0;

uint16_t  redValue = 0;
uint16_t  greenValue = 0;
uint16_t  blueValue = 0;

int main(void)
{
    int factor = 1000/255;		
    
	RCC_Configuration(); //初始化系统时钟
	USART_InitConfig(); //初始化串口
	SysTick_init(72); //初始化系统定时器
	
	InitLedGpio(); 
	InitKey1();
	//InitMyTimer2();
	
	//InitBeepGpio();
	InitPwmLedGpio();
	InitMyTimer3();
	/*
	  串口1将接收到的数据 ---》发回去
	*/

	memset(uart1Buf,0,128);
	uart1RecvLen = 0;
	
	memset(uart3Buf,0,128);
	uart3RecvLen = 0;
	
	
	printf("Start BLE LED\r\n");
	
	SendBleATCmd("AT");
	
	//查询BLE MAC地址
	SendBleATCmd("AT+MAC");


	while(1)
	{		
			if(uart3RecvLen >=9 )
			{
					//将接收数据缓冲区和数据长度清0 等待下次接收	
					//usart1_putstr(uart3Buf,uart3RecvLen);
					if(uart3Buf[8] == CalCRC(uart3Buf+2,6))
					{
						
							//int factor = 1000/255;				
						  //正确接收到 APP LED等控制命令
							redValue = uart3Buf[5] * factor;
							greenValue = uart3Buf[6] *factor ;
							blueValue = uart3Buf[7] *factor;
						
							setRGBPwmWidth(blueValue,greenValue,redValue);			
					}
					else
					{
						 //命令CRC校验错误
						 printf("cmd crc error\r\n");
					}

					memset(uart3Buf,0,128);
					uart3RecvLen = 0;
			}			
	}
	
	return 0;
}
