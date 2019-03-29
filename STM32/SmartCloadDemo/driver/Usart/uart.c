#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

#include "gizwits_product.h"


#pragma import(__use_no_semihosting)  

struct __FILE 
{ 
	int handle; 
}; 


/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       

//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

/* Private functions ---------------------------------------------------------*/

void USART_Configuration(void)//串口初始化函数
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	NVIC_InitTypeDef NVIC_InitStruct;
					
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
					
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);        
	/*
	*  USART1_TX -> PA9 , USART1_RX ->        PA10
	*/                                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;                 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_InitStructure.USART_BaudRate = 115200;//设置串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//设置工作模式
	USART_Init(USART1, &USART_InitStructure); //配置入结构体
	
	//允许串口1接收中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1, ENABLE);//使能串口1
}		



void ClearUART1ITPendFlag(void)
{
	NVIC->ICPR[0] = (1<<27);
}

uint32_t GetUART1ITPendFlag(void)
{
	uint32_t status = 0;
	
	status = NVIC->ICPR[0]; //& (1<<27);
		
	return status;
}


//串口1接收中断

uint8_t recv_buf[100] = {0};
int len = 0;
void USART1_IRQHandler(void)
{
		recv_buf[len] = UART_Recive();
	  len++;
}

void UART_send_byte(uint8_t byte) //发送1字节数据
{
	 while(!((USART1->ISR)&(1<<7)));
	 USART1->TDR=byte;	
}		

void UART_Send(uint8_t *Buffer, uint32_t Length)
{
		while(Length != 0)
		{
			while(!((USART1->ISR)&(1<<7)));//等待发送完
			USART1->TDR= *Buffer;
			Buffer++;
			Length--;
		}
}

uint8_t UART_Recive(void)
{	
		while(!(USART1->ISR & (1<<5)));//等待接收到数据
		return(USART1->RDR);			 //读出数据
}


int fputc(int ch, FILE *f)
{
    /* 将Printf内容发往串口 */
		USART_SendData(USART1,(uint8_t)  ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		{}
	 
		return (ch);
}


//初始化串口2

void USART2_Configuration(void)//串口初始化函数
{  
		GPIO_InitTypeDef  GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	
	  NVIC_InitTypeDef NVIC_InitStruct;
						
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );
						
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);        
		/*
		*  USART1_TX -> PA2 , USART1_RX -> PA3
		*/                                
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;                 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);    

		NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		USART_InitStructure.USART_BaudRate = 9600;//设置串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//设置工作模式
		USART_Init(USART2, &USART_InitStructure); //配置入结构体
		
		//允许串口2接收中断
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		
		USART2->ICR = 1<<3; //清楚溢出标志
	
		USART_Cmd(USART2, ENABLE);  //使能串口2
}		

//串口2接收一个字节
uint8_t UART2_Recive(void)
{	
	  uint32_t reg = USART2->ISR;
	
	//	printf("regvalue: %x\r\n", reg);
	
		while(!(USART2->ISR & (1<<5)));//等待接收到数据
		return(USART2->RDR);			 //读出数据
}

//串口2接收中断
void USART2_IRQHandler(void)
{
	 uint8_t value = 0;
	
	 if( USART2->ISR & (1<<5))
	 {
			USART2->ICR = 1<<3; 
			value = USART2->RDR;//STM32 test demo
			gizPutData(&value, 1);
	 }
	 else
	 {
		   //溢出
		   USART2->ICR = 1<<3; //清楚溢出标志
	 }
	
}

//串口2发送一个字节
void UART2_send_byte(uint8_t byte) //发送1字节数据
{
	 while(!((USART2->ISR)&(1<<7)));
	 USART2->TDR=byte;	
}		

void UART2_Send(uint8_t *Buffer, uint32_t Length)
{
		while(Length != 0)
		{
			while(!((USART2->ISR)&(1<<7)));//等待发送完
			USART2->TDR= *Buffer;
			Buffer++;
			Length--;
		}
}







		
