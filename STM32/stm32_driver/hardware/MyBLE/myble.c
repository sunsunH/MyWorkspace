
/*
 蓝牙模块驱动
 
*/

#include "usart_driver.h"
#include <string.h>
#include "SysTick.h"
#include <stdio.h>



/*

  给蓝牙模块发送AT命令，并且等待返回结果
	
	成功返回 0，失败返回 -1
	
*/
int SendBleATCmd(char *atCmd)
{
	//清空串口3接收缓冲区 准备发送AT命令

	usart3_putstr((uint8_t *)atCmd, strlen(atCmd));
	
	//等待AT命令的响应
	while(uart3RecvLen == 0);  
	
	delay_ms(200);
	printf("BLE AT Ack:%s\r\n", uart3Buf);
	
	memset(uart3Buf,0,128);
	uart3RecvLen = 0;
	

	
	return 0;
	
}


//计数异或校验和
uint8_t  CalCRC(uint8_t *buf, uint8_t len)
{
	 uint8_t  crc_value = 0;
	 uint8_t i = 0;
	
	for(i = 0; i < len; i++)
	{
		crc_value ^= buf[i];
	}
	
	return crc_value;
	
}


