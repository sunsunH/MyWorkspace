
//#include "gpio.h"

#include "stdint.h"
#include "lcd.h"
#include "font_lcd.h"
#include "string.h"

#include "time.h"
#include "SysTick.h"

//static uint8_t lcd_send_data = 0;



//extern  void HalLcd_HW_WaitUs(uint16 i);  
  
/*
 * Initialize LCD Service
 */
 
 //Init LCD GPIO
 /*
 
 MISO -- PB4  -输入模式
 
 MOSI -- PB5
 SCLK -- PB3
 SS   -- PA15
 LCD  -- PB6
 
 */
 
 void Lcd_GPIO_Init(void)
 {
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	//使能PORTB PORTA 时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
 
   	//初始化GPIOB 为输入模式
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //输出工作模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOB,&GPIO_InitStructure);
 
 	//初始化PA15 位输出模式
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //输入工作模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//初始化PB3 PB5 PB6 位输出模式
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //输入工作模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOB,&GPIO_InitStructure);
	 	 
 }

 
 //LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{	
	Lcd_WriteIndex(0x11);//Sleep exit 
	Delay_ms(120);
	Lcd_WriteIndex(0x11);//Sleep exit 
	Delay_ms(120);
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC8); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	Lcd_WriteIndex(0x29);//Display on		
}


void SPI_WriteData(uint8_t Data)
{
	unsigned char i;
	for(i=8; i>0; i--)
	{
		if(Data & 0x80)
		{
			LCD_SDA_SET;              //数据输出高电平
		}
		else
		{
			LCD_SDA_CLR;               //数据输出低电平
		}	
			LCD_SCL_SET;              //时钟高
		  LCD_SCL_CLR;              //时钟低
		  Data  <<=  1;
	}
}

void LCD_WriteData_16Bit(uint16_t Data)
{
	 LCD_CS_CLR;
	 LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据	
	 LCD_CS_SET;
}

//向液晶屏写一个8位指令
void Lcd_WriteIndex(uint8_t Index)
{
   //SPI 写命令时序开始               
	 LCD_CS_CLR;       
	 LCD_RS_CLR;           //LCD_RS_CLR
	 SPI_WriteData(Index);
	 LCD_CS_SET;          
}
//向液晶屏写一个8位数据
void Lcd_WriteData(uint8_t Data)
{
	LCD_CS_CLR;
	LCD_RS_SET;
        SPI_WriteData(Data);
	LCD_CS_SET;
}

void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	LCD_CS_CLR;
	Lcd_WriteIndex(Index);
        Lcd_WriteData(Data);
	LCD_CS_SET;
}


/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);
	
	Lcd_WriteIndex(0x2c);

}
/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}
//取模方式 水平扫描 从左到右 低位在前
void showimage_farsight(const unsigned char *p) //显示128*35 图片
{
  int i; 
	unsigned char picH,picL;
	//Lcd_Clear(WHITE); //清屏  
	Lcd_SetRegion(0,0,127,34);		//坐标设置
	for(i=0;i<128*35;i++)
 {	
	picL=*(p+i*2);	//数据低位在前
	picH=*(p+i*2+1);				
	LCD_WriteData_16Bit(picH<<8|picL);  						
 }		
}

void showimage(const unsigned char *p) //显示128*35 图片
{
  int i; 
	unsigned char picH,picL;
	//Lcd_Clear(WHITE); //清屏  
	Lcd_SetRegion(0,0,127,127);		//坐标设置
	for(i=0;i<128*128;i++)
 {	
	picL=*(p+i*2);	//数据低位在前
	picH=*(p+i*2+1);				
	LCD_WriteData_16Bit(picH<<8|picL);  						
 }		
}


void Gui_DrawFont_GBK16(uint16_t x0, uint16_t y0, uint16_t fc, uint16_t bc, uint8_t *s)
{ 
  int i,j,k,x,y,xx;
  
  unsigned char qm;
  
  long int ulOffset;
  
  char  ywbuf[32];
 // char   temp[2];
  
  for(i = 0; i<strlen((char*)s);i++)
  {
    if(((unsigned char)(*(s+i))) >= 161)
    {
//      temp[0] = *(s+i);
//      temp[1] = '\0';
      return;
    }
    
    else
    {
      qm = *(s+i);
      
      ulOffset = (long int)(qm) * 16;
      
      for (j = 0; j < 16; j ++)
      {
        ywbuf[j]=Zk_ASCII8X16[ulOffset+j];
      }
      
      for(y = 0;y < 16;y++)
      {
        for(x=0;x<8;x++) 
        {
          k=x % 8;
          
          if(ywbuf[y]&(0x80 >> k))
          {
            xx=x0+x+i*8;     
            Gui_DrawPoint(xx,y+y0,fc);
          }
          else
          {
            xx=x0+x+i*8;     
            Gui_DrawPoint(xx,y+y0,bc);
          }  
        }
      }
      
    }
  }  
}

