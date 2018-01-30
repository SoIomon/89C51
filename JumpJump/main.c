#include <reg51.h>
#include <intrins.h>

typedef unsigned char u16;

#define GPIO_KEY P1

sbit DUOJI=P0^1;

unsigned int KeyValue;	//存放键值
int purse;

void Delay250us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 122;
	while (--i);
}

void Delay(u16 i)
{
	while(i--);
}

void fang()
{
	int t,i;
	for(t=0;t<20;t++)
	{
		DUOJI = 1;
		Delay250us();
		Delay250us();
		Delay250us();
		Delay250us();
		DUOJI = 0;
		for(i=0;i<76;i++)
		{
			Delay250us();
		}
	}
}

void shou()
{
	int t,i;
	for(t=0;t<20;t++)
	{
		DUOJI = 1;
		Delay250us();
		Delay250us();
		Delay250us();
		Delay250us();
		Delay250us();
		Delay250us();
		DUOJI = 0;
		for(i=0;i<74;i++)
		{
			Delay250us();
		}
	}
}


void KeyDown()
{
	int time=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Delay(1000);
		if(GPIO_KEY!=0x0f)
		{	
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((time<50)&&(GPIO_KEY!=0xf0))
			{
				Delay(1000);
				time++;
			}
		}
			purse = 1;
	}
}

void aaa()
{
	int i,j;
	do{
	KeyDown();
	}while(purse == 0);
	if(purse==1)
	{
		//具体关系有待计算
		j = (int)(KeyValue*150*1.35);
		
		shou();
		for(i=0;i<j*4;i++)
		{
			Delay250us();
		}
		purse = 0;
		fang();
	}
}

void main()
{
	int i;
	DUOJI = 0;
	for(i=0;i<50;i++)
		Delay250us();
	while(1)
	{
		fang();
		aaa();
	}
}
