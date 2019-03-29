#ifndef _DHT11_
#define _DHT11_


typedef  unsigned char u8;

extern u8 tempx;
extern u8 humix;


//IO方向设置
#define DHT11_IO_IN()  {GPIOB->MODER&=~(3<<(8*2));GPIOB->MODER|=0<<8*2;}	//PB8输入模式
#define DHT11_IO_OUT() {GPIOB->MODER&=~(3<<(8*2));GPIOB->MODER|=1<<8*2;} 	//PB8输出模式 


#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)  //数据端口	PB8

u8 DHT11_Init(void);	//初始化DHT11
u8 DHT11_Read_Data(u8 *temp, u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);	//检测是否存在DHT11
void DHT11_Rst(void);	//复位DHT11



#endif 

