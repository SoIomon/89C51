#include "reg52.h"	
#include <math.h>

typedef unsigned int u16;	
typedef unsigned char u8;

#define GPIO_KEY P1
#define StartStopKey 5
#define PlusKey 1
#define SubKey 9
#define RightSwitch 6
#define LeftSwitch 4
#define ModSwitch 15

sbit Beep=P1^5;
sbit ModLed=P2^0;
sbit RelayLed=P2^1;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

int Count10ms = 0;
int Count1s = 0;
int TimeArr[3] = {0};
int MODValue = 0;
int StartFlag = 0;
int KeyValue = 0;
int SetTimeBit = 0;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x40,0x40};

void TimerInit();
void Timer();	
void ResetInit();
void ResetTimer();
void delay(u16 i);
void DigDisplayTime();
void KeyDown();
void CountDown();
void SetTime();

void main()
{	
	TimerInit();
	ResetInit();
	while(1)
	{	
		RelayLed =~ ModLed;
		if(StartFlag)
			CountDown();
		else
			SetTime();
	}
}

void TimerInit()		//0.01s  10ms
{
	TMOD = 0x01;
	TH0 = 0xDC;
	TL0 = 0x00;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	TimeArr[0] = 0;
}

void Timer() interrupt 1
{
	TH0 = 0xDC;
	TL0 = 0x00;
	Count10ms++;
	Count1s++;
	if(Count1s == 100)
	{
		if(StartFlag == 1)
		{
			if(TimeArr[0] == 0)
			{
				if(TimeArr[1])
				{
					TimeArr[1]--;
					TimeArr[0] = 60;
				}
				else
				{
					if(TimeArr[2])
					{
						TimeArr[2]--;
						TimeArr[1] = 59;
						TimeArr[0] = 60;
					}
					else
					{
						StartFlag = 0;
					}
				}
			}
			TimeArr[0]--;
		}
		Count1s = 0;
	}
	if(Count10ms == 2)
	{
		KeyDown();
		DigDisplayTime();
		Count10ms = 0;
	}
}

void ResetInit()
{
	EA = 1;
	EX0 = 1;
	IT0 = 1;
}

void ResetTimer() interrupt 0
{
	TH0 = 0xDC;
	TL0 = 0x00;
	TimeArr[0] = 0;
	TimeArr[1] = 0;
	TimeArr[2] = 0;
}

void delay(u16 i)
{
	while(i--);	
}

void DigDisplayTime()
{
	int i,value;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0):
				LSA=0;LSB=0;LSC=0;value=TimeArr[0]%10; break;
			case(1):
				LSA=1;LSB=0;LSC=0;value=TimeArr[0]/10; break;
			case(2):
				LSA=0;LSB=1;LSC=0;value=11; break;
			case(3):
				LSA=1;LSB=1;LSC=0;value=TimeArr[1]%10; break;
			case(4):
				LSA=0;LSB=0;LSC=1;value=TimeArr[1]/10; break;
			case(5):
				LSA=1;LSB=0;LSC=1;value=11; break;
			case(6):
				LSA=0;LSB=1;LSC=1;value=TimeArr[2]%10; break;
			case(7):
				LSA=1;LSB=1;LSC=1;value=TimeArr[2]/10; break;	
		}
		P0=smgduan[value];
		delay(50); 
		P0=0x00;
	}
}

void KeyDown()
{
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Beep =~ Beep;
		delay(1000);
		Beep =~ Beep;
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
			while(GPIO_KEY!=0xf0);
		}
	}
	else
		KeyValue = 0;
}

void CountDown()
{
	u8 i;
	if((TimeArr[1] || TimeArr[2]) == 0 && TimeArr[0] < 5)
	{
		for(i=0;i<100;i++)
		{
			Beep =~ Beep;
			delay(100);
		}
	}
	if((TimeArr[0] || TimeArr[1] || TimeArr[2]) == 0)
	{
		StartFlag = 0;
		RelayLed =~ RelayLed;
		ModLed =~ ModLed;
	}
}

void SetTime()
{
	switch(KeyValue)
	{
		case(StartStopKey): StartFlag = 1;break;
		case(LeftSwitch):  SetTimeBit=(SetTimeBit+1)%3;break;
		case(RightSwitch):	SetTimeBit=abs((SetTimeBit-1))%3;break;
		case(PlusKey): 	TimeArr[SetTimeBit]++;break;
		case(SubKey): 	TimeArr[SetTimeBit]=abs((TimeArr[SetTimeBit]-1))%100;break;
		case(ModSwitch):	ModLed =~ ModLed;RelayLed=~ModLed;break;
		default:break;
	}
	KeyValue = 0;
}