#include "reg52.h"	

typedef unsigned int u16;	
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x40,0x00};

void delay(u16 i);
void DigDisplay(int num);
void DigDisplayfloat(float num);
void itoa(int num,int arr[]);

void main()
{	
	while(1)
	{	
		DigDisplayfloat(1.1);
	}		
}

void delay(u16 i)
{
	while(i--);	
}

void DigDisplay(int num)
{
	int i;
	int arr[8];
	itoa(num,arr);
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;
			case(1):
				LSA=1;LSB=0;LSC=0; break;
			case(2):
				LSA=0;LSB=1;LSC=0; break;
			case(3):
				LSA=1;LSB=1;LSC=0; break;
			case(4):
				LSA=0;LSB=0;LSC=1; break;
			case(5):
				LSA=1;LSB=0;LSC=1; break;
			case(6):
				LSA=0;LSB=1;LSC=1; break;
			case(7):
				LSA=1;LSB=1;LSC=1; break;	
		}
		P0=smgduan[arr[i]];
		delay(100); 
		P0=0x00;
	}
}

void DigDisplayfloat(float num)
{
	int i;
	int arr[8];
	itoa(num*100,arr);
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;
			case(1):
				LSA=1;LSB=0;LSC=0; break;
			case(2):
				LSA=0;LSB=1;LSC=0; break;
			case(3):
				LSA=1;LSB=1;LSC=0; break;
			case(4):
				LSA=0;LSB=0;LSC=1; break;
			case(5):
				LSA=1;LSB=0;LSC=1; break;
			case(6):
				LSA=0;LSB=1;LSC=1; break;
			case(7):
				LSA=1;LSB=1;LSC=1; break;	
		}
		if(i==2)
			P0=smgduan[arr[i]]+0x80;
		else
			P0=smgduan[arr[i]];
		delay(100); 
		P0=0x00;
	}
}

void itoa(int num,int arr[])
{
	int j;
	if(num<0)
	{
		arr[7] = 10;
		num = -num;
	}
	else
		arr[7]=num/1e7;
	for(j=0;j<7;j++)
	{
		arr[j]=num%10;
		num/=10;
	}
}
