
/*
 ����ģ������
 
*/

#include "usart_driver.h"
#include <string.h>
#include "SysTick.h"
#include <stdio.h>



/*

  ������ģ�鷢��AT������ҵȴ����ؽ��
	
	�ɹ����� 0��ʧ�ܷ��� -1
	
*/
int SendBleATCmd(char *atCmd)
{
	//��մ���3���ջ����� ׼������AT����

	usart3_putstr((uint8_t *)atCmd, strlen(atCmd));
	
	//�ȴ�AT�������Ӧ
	while(uart3RecvLen == 0);  
	
	delay_ms(200);
	printf("BLE AT Ack:%s\r\n", uart3Buf);
	
	memset(uart3Buf,0,128);
	uart3RecvLen = 0;
	

	
	return 0;
	
}


//�������У���
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


