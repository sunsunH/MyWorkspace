/***********************************************************
**�ļ����ܣ�USART���ڲ����ļ�
**�ӿڶ��壺���ö˿�
**			USART1_Tx-----------GPIOA9
**			USART1_Rx-----------GPIOA10
************************************************************/

#include "stm32f10x.h"
#include "usart_driver.h"

/* Private function prototypes -----------------------------------------------*/



#pragma import(__use_no_semihosting_swi)  

struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 


/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       

//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 


/***************************************
**USART1

 UART1_TXD--->PA9
 UART1_RXD--->PA10

****************************************/
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	USART_DeInit(USART1);
	
	//��UART1 �� GPIOA ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*����UART1�Ĺ�����ʽ
	
	������: 115200
	����λ: 8λ����λ
	1λֹͣλ  ��У�� 
	��Ӳ������
	�����ͺͽ��չ���
	
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	//������1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	
	//��SR�Ĵ�����6λ��0
	USART1->SR &= ~(0x01<<6);
	
	USART_Cmd(USART1, ENABLE);
}


//���ô��ڵ������к��ж����ȼ�
void UASRT_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);

		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}

int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}



//���ڷ���һ���ֽڵĺ���
char usart1_putc(char ch)
{
	USART_SendData(USART1, (uint8_t) ch);
	
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);		

	return (ch);
}

int usart1_putstr(unsigned char* buff,int len)
{
	int i = 0;
	
	for(i = 0;i < len;i++)
	{
		usart1_putc(buff[i]);
	}

	return len;
}

char usart1_getc(void)
{
	char temp = 0;
	
	//�ȴ����ڽ�������
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!= SET); 
	
	temp = USART_ReceiveData(USART1);

	return temp;
}

int usart1_getstr(unsigned char* buff,int len)
{
	int i = 0;

	for(i = 0;i < len;i++)
	{
		buff[i] = usart1_getc();
	}

	return len;
}


/************************************************************************
USART3_TX --->PB10
USART3_RX --->PB11

USART3 ��ʼ������
*************************************************************************/
void USART3_Config(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART3 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	USART_DeInit(USART3);
	
		/* USART3 GPIO config */
	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART3, ENABLE);
}


//����3����һ���ֽڵĺ���
char usart3_putc(char ch)
{
	USART_SendData(USART3, (uint8_t) ch);
	
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) != SET);		

	return (ch);
}

//ͨ������3����һ���ֽ�
char usart3_getc(void)
{
	char temp = 0;
	
	//�ȴ�����3������ 
	while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE)!= SET);
	
	temp = USART_ReceiveData(USART3);

	return temp;
}


//ͨ������3����һ���ַ���
int usart3_putstr(unsigned char* buff,int len)
{
	int i = 0;
	
	for(i = 0;i < len;i++)
	{
		usart3_putc(buff[i]);
	}

	return len;
}


//�����ַ���
int usart3_getstr(unsigned char* buff,int len)
{
	int i = 0;

	for(i = 0;i < len;i++)
	{
		buff[i] = usart3_getc();
	}
	return len;
}


void USART_InitConfig(void)
{
	UASRT_NVIC_Configuration();
	USART1_Config();
	USART3_Config();
}


