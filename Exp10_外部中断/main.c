#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit led = P2^0;
sbit k3 = P3^2;

void delay(u16 i);
void Int0Init();	//外部中断0的初始化
void Int0();		//中断函数

void main()
{
	while(1)
	{
		Int0Init();
	}
	led = 0;
}

void delay(u16 i)
{
	while(i--);
}

void Int0Init()
{
	EA = 1;
	EX0 = 1;
	IT0 = 1;
}

void Int0()	interrupt 0
{
	//delay(1000);
	if(k3 == 0)
		led =~ led;
}