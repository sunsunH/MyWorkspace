

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
	USART_Configuration(); //初始化串口
	
	Delay_ms(1000);
	
	USART2_Configuration(); //初始化串口2
	
	EXIT_KEY_Init();
	
	//Timer3用于更新协议定时时间
	TIM3_INT_Config();
	TIM3_Config();
	
	TIM2_Config(); // Timer2用来实现us级延时
	
	DHT11_Init();
	
	Lcd_GPIO_Init();
	Lcd_Init();
	Lcd_Clear(YELLOW) ;
	Gui_DrawFont_GBK16(0,0,RED,CYAN,"  good ");
	
	
	userInit();
	
	//完成 gizwits通信协议初始化 
	gizwitsInit();
	
	
	//恢复模组出厂参数配置
	gizwitsSetMode(WIFI_RESET_MODE);
	
	//设置模组为AIRLINK_MODE参数配置模式
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
		
		//用户数据处理函数,用户需要更改该函数，将传感器数据读取到 currentDataPoint
		//变量中
		userHandle();
	
		//完成下行数据处理和上行数据汇报，协议栈API函数，无需更改
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
		
	}
	
	return 0;
}

