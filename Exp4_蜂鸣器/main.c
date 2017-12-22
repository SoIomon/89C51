#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit beep = P1^5;
sbit led = P2^0;

void delay(u16 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
		led =~ led;
		beep =~ beep;
		delay(50000);
	}
}