
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
    
	RCC_Configuration(); //��ʼ��ϵͳʱ��
	USART_InitConfig(); //��ʼ������
	SysTick_init(72); //��ʼ��ϵͳ��ʱ��
	
	InitLedGpio(); 
	InitKey1();
	//InitMyTimer2();
	
	//InitBeepGpio();
	InitPwmLedGpio();
	InitMyTimer3();
	/*
	  ����1�����յ������� ---������ȥ
	*/

	memset(uart1Buf,0,128);
	uart1RecvLen = 0;
	
	memset(uart3Buf,0,128);
	uart3RecvLen = 0;
	
	
	printf("Start BLE LED\r\n");
	
	SendBleATCmd("AT");
	
	//��ѯBLE MAC��ַ
	SendBleATCmd("AT+MAC");


	while(1)
	{		
			if(uart3RecvLen >=9 )
			{
					//���������ݻ����������ݳ�����0 �ȴ��´ν���	
					//usart1_putstr(uart3Buf,uart3RecvLen);
					if(uart3Buf[8] == CalCRC(uart3Buf+2,6))
					{
						
							//int factor = 1000/255;				
						  //��ȷ���յ� APP LED�ȿ�������
							redValue = uart3Buf[5] * factor;
							greenValue = uart3Buf[6] *factor ;
							blueValue = uart3Buf[7] *factor;
						
							setRGBPwmWidth(blueValue,greenValue,redValue);			
					}
					else
					{
						 //����CRCУ�����
						 printf("cmd crc error\r\n");
					}

					memset(uart3Buf,0,128);
					uart3RecvLen = 0;
			}			
	}
	
	return 0;
}
