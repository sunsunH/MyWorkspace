#ifndef _USART_DRIVER_H_
#define _USART_DRIVER_H_


#include <stdio.h>
#include "stm32f10x.h"




/***************************************
**USART1
****************************************/
void USART1_Config(void);
void UASRT_NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

char usart1_putc(char ch);
int usart1_putstr(unsigned char* buff,int len);
char usart1_getc(void);
int usart1_getstr(unsigned char* buff,int len);

extern uint8_t uart1Buf[128];
extern uint8_t uart1RecvLen ; //保存串口1接收到的数据的长度

extern uint8_t uart3Buf[128];
extern uint8_t uart3RecvLen ; //保存串口3接收到的数据的长度

/***************************************
**USART3
****************************************/
void USART3_Config(void);
char usart3_putc(char ch);
char usart3_getc(void);

int usart3_putstr(unsigned char* buff,int len);
int usart3_getstr(unsigned char* buff,int len);



void USART_InitConfig(void);

#endif
