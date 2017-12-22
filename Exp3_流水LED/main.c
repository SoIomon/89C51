#include <reg52.h>
#include <intrins.h>

#define led P2

typedef unsigned char u8;
typedef unsigned int u16;

sbit beep = P1^5;

void delay(u16 i)
{
	while(i--);
}

void main()
{
	u8 i;
	led = 0xff;
	delay(10000);
	while(1)
	{
		for(i=0;i<7;i++)
		{
			beep =~ beep;
			led = _crol_(led,1);
			delay(10000);
		}
	}
}