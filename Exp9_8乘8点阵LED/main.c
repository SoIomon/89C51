#include <reg51.h>
typedef unsigned char u8;
typedef unsigned int u16;

//管脚定义
sbit SRCLK = P3^6;
sbit RCLK = P3^5;
sbit SER = P3^4;

void delay(u16 i);
void Hc595SendByte(u8 byte);

//数据显示
u8 ledduanxuan[]={0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};
u8 ledweixuan[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void main()
{
	u8 i;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P0 = ledweixuan[i];
			Hc595SendByte(ledduanxuan[i]);
			delay(100);
			Hc595SendByte(0x00);
		}
	}
}

void delay(u16 i)
{
	while(i--);
}

void Hc595SendByte(u8 byte)
{
	u8 i = 0;
	SRCLK = 0;
	RCLK = 0;
	for(i=0;i<8;i++)
	{
		SER = byte>>7;
		byte<<=1;
		SRCLK = 1;
		SRCLK = 0;
	}
	RCLK = 1;
	RCLK = 0;
}