#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

#include "gizwits_product.h"


#pragma import(__use_no_semihosting)  

struct __FILE 
{ 
	int handle; 
}; 


/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       

//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

/* Private functions ---------------------------------------------------------*/

void USART_Configuration(void)//���ڳ�ʼ������
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
	
	USART_InitStructure.USART_BaudRate = 115200;//���ô��ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����Ч��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ù���ģʽ
	USART_Init(USART1, &USART_InitStructure); //������ṹ��
	
	//������1�����ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1, ENABLE);//ʹ�ܴ���1
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


//����1�����ж�

uint8_t recv_buf[100] = {0};
int len = 0;
void USART1_IRQHandler(void)
{
		recv_buf[len] = UART_Recive();
	  len++;
}

void UART_send_byte(uint8_t byte) //����1�ֽ�����
{
	 while(!((USART1->ISR)&(1<<7)));
	 USART1->TDR=byte;	
}		

void UART_Send(uint8_t *Buffer, uint32_t Length)
{
		while(Length != 0)
		{
			while(!((USART1->ISR)&(1<<7)));//�ȴ�������
			USART1->TDR= *Buffer;
			Buffer++;
			Length--;
		}
}

uint8_t UART_Recive(void)
{	
		while(!(USART1->ISR & (1<<5)));//�ȴ����յ�����
		return(USART1->RDR);			 //��������
}


int fputc(int ch, FILE *f)
{
    /* ��Printf���ݷ������� */
		USART_SendData(USART1,(uint8_t)  ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		{}
	 
		return (ch);
}


//��ʼ������2

void USART2_Configuration(void)//���ڳ�ʼ������
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
		
		USART_InitStructure.USART_BaudRate = 9600;//���ô��ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����Ч��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ù���ģʽ
		USART_Init(USART2, &USART_InitStructure); //������ṹ��
		
		//������2�����ж�
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		
		USART2->ICR = 1<<3; //��������־
	
		USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
}		

//����2����һ���ֽ�
uint8_t UART2_Recive(void)
{	
	  uint32_t reg = USART2->ISR;
	
	//	printf("regvalue: %x\r\n", reg);
	
		while(!(USART2->ISR & (1<<5)));//�ȴ����յ�����
		return(USART2->RDR);			 //��������
}

//����2�����ж�
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
		   //���
		   USART2->ICR = 1<<3; //��������־
	 }
	
}

//����2����һ���ֽ�
void UART2_send_byte(uint8_t byte) //����1�ֽ�����
{
	 while(!((USART2->ISR)&(1<<7)));
	 USART2->TDR=byte;	
}		

void UART2_Send(uint8_t *Buffer, uint32_t Length)
{
		while(Length != 0)
		{
			while(!((USART2->ISR)&(1<<7)));//�ȴ�������
			USART2->TDR= *Buffer;
			Buffer++;
			Length--;
		}
}







		
