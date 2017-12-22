#include <reg52.h>
#define led1 P0
#define led2 P1
#define led3 P2
#define led4 P3

//sbit led = P2^0;

void main()
{
	while(1)
	{
		led1 = 0xff;
		led2 = 0xff;
		led3 = 0xff;
		led4 = 0xff;
	}
}