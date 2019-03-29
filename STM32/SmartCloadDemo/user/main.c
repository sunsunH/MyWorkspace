

#include "stdio.h"

#include "Led.h"
#include "SysTick.h"
#include "uart.h"
#include "string.h"

#include "key.h"
#include "time.h"

#include "gizwits_product.h"
#include "common.h"
#include "lcd.h"
#include "DHT11.h"

/*
 main.c
*/

int count = 0;

extern uint8_t recv_buf[100];
extern int len;

uint8_t tempx = 0;
uint8_t humix=0;

char strDisp[50] = {0};


int  main(void)
{
	initLedGpio();
	Systick_Init();
	USART_Configuration(); //��ʼ������
	
	Delay_ms(1000);
	
	USART2_Configuration(); //��ʼ������2
	
	EXIT_KEY_Init();
	
	//Timer3���ڸ���Э�鶨ʱʱ��
	TIM3_INT_Config();
	TIM3_Config();
	
	TIM2_Config(); // Timer2����ʵ��us����ʱ
	
	DHT11_Init();
	
	Lcd_GPIO_Init();
	Lcd_Init();
	Lcd_Clear(YELLOW) ;
	Gui_DrawFont_GBK16(0,0,RED,CYAN,"  good ");
	
	
	userInit();
	
	//��� gizwitsͨ��Э���ʼ�� 
	gizwitsInit();
	
	
	//�ָ�ģ�������������
	gizwitsSetMode(WIFI_RESET_MODE);
	
	//����ģ��ΪAIRLINK_MODE��������ģʽ
	gizwitsSetMode(WIFI_AIRLINK_MODE);
	
	
	turnOnOffLed(1);
	turnOnOffLed(0);
	
	while(1)
	{
	
		DHT11_Read_Data(&tempx,&humix);
		
		printf("temp: %d  humi:%d \r\n", tempx, humix);
		
		sprintf(strDisp,"Temperatue: %d", tempx);
		Gui_DrawFont_GBK16(0,16,RED,CYAN,(uint8_t *)strDisp);
		
		sprintf(strDisp,"Humidity: %d", humix);
		Gui_DrawFont_GBK16(0,32,RED,CYAN,(uint8_t *)strDisp);
		
		//�û����ݴ�����,�û���Ҫ���ĸú����������������ݶ�ȡ�� currentDataPoint
		//������
		userHandle();
	
		//����������ݴ�����������ݻ㱨��Э��ջAPI�������������
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
		
	}
	
	return 0;
}

