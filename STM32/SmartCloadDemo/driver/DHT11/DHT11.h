#ifndef _DHT11_
#define _DHT11_


typedef  unsigned char u8;

extern u8 tempx;
extern u8 humix;


//IO��������
#define DHT11_IO_IN()  {GPIOB->MODER&=~(3<<(8*2));GPIOB->MODER|=0<<8*2;}	//PB8����ģʽ
#define DHT11_IO_OUT() {GPIOB->MODER&=~(3<<(8*2));GPIOB->MODER|=1<<8*2;} 	//PB8���ģʽ 


#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)  //���ݶ˿�	PB8

u8 DHT11_Init(void);	//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp, u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);	//����Ƿ����DHT11
void DHT11_Rst(void);	//��λDHT11



#endif 
