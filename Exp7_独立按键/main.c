#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit led = P2^0;
sbit k1 = P3^1;

void delay(u16 i);
void keypurse();

void main()
{
	while(1)
	{
		keypurse();
	}
}

void delay(u16 i)
{
	while(i--);
}

void keypurse()
{
	if(k1==0)
	{
		delay(1000);
		if(k1==0)
		{
			led =~ led;
		}
		while(!k1);
	}
}