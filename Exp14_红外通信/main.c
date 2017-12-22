#include <reg52.h>

typedef	unsigned	int	u16;
typedef	unsigned	char u8;

sbit	P2_2 = P2^2;

void 	Delay(u16 i);		//��ʱ����	
void	Timer0Init();		//�����ȼ��Ķ�ʱ�������ڲ���38kHz�ķ����ź�
void	Timer0();
void	SendBit(u16 b);		//����һλ����
void	SendCmd();

void main()
{
	Timer0Init(); 
	P2_2 = 0;
	while(1)
	{
		SendCmd();
		Delay(100000);
	}
}

void Delay(u16 i)
{
	while(i--);
}

void	Timer0Init()
{
		TMOD|= 0x02;	//������ʽ2��8λ��װ�ض�ʱ��                    
    TL0 = 0xF3;	
		TH0 = 0xF3;
	
		PT0 = 1;			//�����ȼ�
    TR0 = 0; 			//��ʱ����ͣλ
	
    ET0 = 1; 			//�ж�����
    EA = 1;				//���жϿ���
}

/*********************************
���ܣ�38kHz�����ź�
*********************************/
void	Timer0() interrupt 1
{
	P2_2 =~ P2_2;
}

/*********************************
���ܣ�����һλ����
*********************************/
void	SendBit(u16 b)
{
	TL0 = 0xF3;	
	TH0 = 0xF3;
	TR0 = 1;
	Delay(33);
	TR0 = 0;
	if(b)
		Delay(170);
	else
		Delay(46);
}

void	SendCmd()
{
	u16	Comd1[3] = {0xC050,0x040A,0x4000};
	u16 Comd2[3] = {0x0044,0x0009,0x8000};
	int i,j;
	TL0 = 0xF3;	
	TH0 = 0xF3;
	TR0 = 1;
	Delay(470);
	TR0 = 0;
	Delay(500);
	for(i=0;i<2;i++)
	{
		for(j=0;j<16;j++)
		{
			SendBit(Comd1[i] & 0x8000);
			Comd1[i] <<= 1;
		}
	}
	for(i=0;i<4;i++)
	{
		SendBit(Comd1[2] & 0x8000);
		Comd1[2] <<= 1;
	}
	Delay(2200);
	for(i=0;i<2;i++)
	{
		for(j=0;j<16;j++)
		{
			SendBit(Comd2[i] & 0x8000);
			Comd2[i] <<= 1;
		}
	}
	SendBit(Comd2[2] & 0x8000);
	TR0 = 0;
}

