#include <reg52.h>
#define led P0

typedef unsigned char u8;
typedef unsigned int u16;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
									   0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
sbit  a = P2^2;
sbit  b = P2^3;
sbit  c = P2^4;
sbit  le = P1^0;

void delay(u16 i);

void main()
{
	u8 i;
	a = 0;
	b = 0;
	c = 0;
	le = 1;
	led = smgduan[2];
	le = 0;
	while(1)
	{
		for(i=0;i<17;i++)
		{
			le = 1;
			led = smgduan[i%16];
			le = 0;
			delay(50000000);
		}
	}
}

void delay(u16 i)
{
	while(i--);
}