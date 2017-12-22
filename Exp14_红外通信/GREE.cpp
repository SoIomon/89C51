#include <stdio.h>

void InitProcess();
void Merge();
void Reversal();

char CMD1[14] = {0x06,//[0]3位模式设置,默认送风
    0x00,//[1]1位开关机,默认关机 
    0x00,//[2]2位风速,默认自动
    0x00,//[3]1位扫风,默认关闭
    0x00,//[4]1位睡眠.默认关闭
    0x05,//[5]4位温度,默认26℃
    0x00,//[6]8位定时,默认关闭
    0x00,//[7]1位超强,默认普通
    0x01,//[8]1位灯光,默认开启
    0x00,//[9]1位健康,默认普通
    0x00,//[10]1位干燥,默认关闭
    0x00,//[11]1位换气,默认关闭
    0x0A,//[12]7位默认值
    0x02 //[13]3位默认值
     };
     
char CMD2[9] = {0x00,//[0]1位上下扫风,默认关闭
   0x00,//[1]3位默认值
   0x00,//[2]1位左右扫风.默认关闭
   0x00,//[3]3位默认值
   0x01,//[4]2位温度显示,默认显示室内温度
   0x04,//[5]6位默认值
   0x00,//[6]8位默认值
   0x00,//[7]4位默认值
   0x09,//[8]4位校验码 
     };

char condition[8] = {};

char receive[7];

char SLEEPTIME[49] = {0x00,0x90,0x18,0x98,0x14,0x94,0x1C,
 0x9C,0x12,0x92,0x1A,0x9A,0x16,0x96,
 0x1E,0x9E,0x11,0x91,0x19,0x99,0x50,
 0xD0,0x58,0xD8,0x54,0xD4,0x5C,0xDC,
 0x52,0xD2,0x5A,0xDA,0x56,0xD6,0x5E,
 0xDE,0x51,0xD1,0x59,0xD9,0x30,0xB0,
 0x38,0xB8,0x34,0xB4,0x3C,0xBC,0x32};
 

int mode = 3;
int temp = 10;

void Switch(int S){
    if(S == 1){
        CMD1[1] = 0x01;    //开机 
    }else if(S == 0){
        CMD1[1] = 0x00;    //关机 
    }
}

void RunInit(){
    CMD1[0] = 0x06;
    CMD1[1] = 0x00;
    CMD1[2] = 0x00;
    CMD1[3] = 0x00;
    CMD1[4] = 0x00;
    CMD1[5] = 0x05;
    CMD1[6] = 0x00;
    CMD1[7] = 0x00;
    CMD1[8] = 0x01;
    CMD1[9] = 0x00;
    CMD1[10] = 0x00;
    CMD1[11] = 0x00;
    CMD1[12] = 0x0A;
    CMD2[0] = 0x00;
    CMD2[1] = 0x00;
    CMD2[2] = 0x00;
    CMD2[3] = 0x00;
    CMD2[4] = 0x01;
    CMD2[5] = 0x04;
    CMD2[6] = 0x00;
    CMD2[7] = 0x00;
    CMD2[8] = 0x09;
}

void Mode(int mode){
    if(mode == 0){
        CMD1[0] = 0x00;   //自动
    }else if(mode == 1){
        CMD1[0] = 0x04;   //制冷
    }else if(mode == 2){
        CMD1[0] = 0x02;   //加湿
    }else if(mode == 3){
        CMD1[0] = 0x06;   //送风
    }else if(mode == 4){
        CMD1[0] = 0x01;    //制热
    }
}

void Wind(int wind){
    if(wind == 0){
        CMD1[2] = 0x00;    //自动
    }else if(wind == 1){
        CMD1[2] = 0x02;    //一级 
    }else if(wind == 2){
        CMD1[2] = 0x01;    //二级
    }else if(wind == 3){
        CMD1[2] = 0x03;    //三级
    }
}

void Sweep(int sweep){
    if(sweep == 0){
        CMD1[3] = 0x00;    //无扫风
        CMD2[0] = 0x00;
        CMD2[2] = 0x00;
    }else if(sweep == 1){
        CMD1[3] = 0x01;    //上下扫风
        CMD2[0] = 0x01;
        CMD2[2] = 0x00;
    }else if(sweep == 2){
        CMD1[3] = 0x01;    //左右扫风
        CMD2[0] = 0x00;
        CMD2[2] = 0x01;
    }else if(sweep == 3){
        CMD1[3] = 0x01;    //上下左右扫风
        CMD2[0] = 0x01;
        CMD2[2] = 0x01;
    }
}

void Sleep(int sleep){
    if(sleep == 1){
        CMD1[4] = 0x01;    //睡眠
    }else if(sleep == 0){
        CMD1[4] = 0x00;    //不睡眠
    }
}

void SleepTime(int sleepTime){
    CMD1[6] = SLEEPTIME[sleepTime];    //睡眠时间
}

void Temp(int temp){
//    CMD1[6] = TEMP[temp];             //温度
    int i;
    char TEMP = 0x00,Bit = 0x00,value = 0x00;
    for(;temp > 0;temp --){
          TEMP++;
    }
    for(i = 0;i < 4;i++){
        Bit = TEMP & 0x01;
        value <<= 1;
        value = value | Bit;
        TEMP >>= 1;
        Bit = 0;    
    }
    CMD1[5] = value;
}

void Super(int super){
    if(super == 0){
        CMD1[7] = 0x00;    //普通模式
    }else if(super == 1){
        CMD1[7] = 0x01;    //超强模式  
    }
}

void Light(int light){
    if(light == 0){
        CMD1[8] = 0x00;   //关闭灯光
    }else if(light == 1){
        CMD1[8] = 0x01;   //开启灯光
    }
}

void Health(int health){
    if(health == 0){
        CMD1[9] = 0x00;   //普通
        CMD1[11] = 0x00;
    }else if(health == 1){
        CMD1[9] = 0x00;   //换气
        CMD1[11] = 0x01;
    }else if(health == 2){
        CMD1[9] = 0x01;   //健康
        CMD1[11] = 0x00;
    }else if(health == 3){
        CMD1[9] = 0x01;   //健康+换气
        CMD1[11] = 0x01;
    }
}

void Heat(int heat){
    if(heat == 0){
        CMD1[10] = 0x00;  //普通
    }else if(heat == 1){
        CMD1[10] = 0x01;  //干燥/辅热
    }
}

void Display(int D){
    if(D == 0){
        CMD2[4] = 0x00;   //不显示
    }else if(D == 1){
        CMD2[4] = 0x02;   //显示  
    }else if(D == 2){
        CMD2[4] = 0x01;   //显示室内
    }else if(D == 3){
        CMD2[4] = 0x03;   //显示室外
    }
}

void Check(int mode,int temp){
    int value = (mode - 1) + temp + 5 + CMD2[2] + CMD1[11] + 0;
    char CHECK = 0x00,check = 0x00,Bit = 0x00;
    int i;
    for(;value > 0;value --){
          CHECK++;
    }
    for(i = 0;i < 4;i++){
        Bit = CHECK & 0x01;
        check <<= 1;
        if(i == 3 && CMD1[1] == 0x00){
            Bit = ~Bit;
            Bit = Bit & 0x01;
        }
        check = check | Bit;
        CHECK >>= 1;
        Bit = 0;    
    }
    CMD2[8] = check;
}

void process(){
    InitProcess();  //初始化
    Merge();        //合并
    Reversal();     //反转
}

void InitProcess(){
    int i;
    for(i = 0;i < 8;i++){
        condition[i] = 0x00;
    }
}

void Merge(){
    condition[0] = condition[0] | CMD1[0];
    condition[0] <<= 1;
    condition[0] = condition[0] |CMD1[1];
    condition[0] <<= 2;
    condition[0] = condition[0] | CMD1[2];
    condition[0] <<= 1;
    condition[0] = condition[0] | CMD1[3];
    condition[0] <<= 1;
    condition[0] = condition[0] | CMD1[4];

    condition[1] = condition[1] | CMD1[5];
    condition[1] <<= 4;
    condition[1] = condition[1] | ((CMD1[6] >>= 4) & 0x0F);

    condition[2] = condition[2] | ((CMD1[6] <<= 4) & 0x0F);
    condition[2] <<= 4;
    condition[2] = condition[2] | CMD1[7];
    condition[2] <<= 1;
    condition[2] = condition[2] | CMD1[8];
    condition[2] <<= 1;
    condition[2] = condition[2] | CMD1[9];
    condition[2] <<= 1;
    condition[2] = condition[2] | CMD1[10];

    condition[3] = condition[3] | CMD1[11];
    condition[3] <<= 7;
    condition[3] = condition[3] | CMD1[12];

    condition[4] = condition[4] | CMD2[0];
    condition[4] <<= 3;
    condition[4] = condition[4] | CMD2[1];
    condition[4] <<= 1;
    condition[4] = condition[4] | CMD2[2];
    condition[4] <<= 3;
    condition[4] = condition[4] | CMD2[3];

    condition[5] = condition[5] | CMD2[4];
    condition[5] <<= 6;
    condition[5] = condition[5] | CMD2[5];

    condition[6] = condition[6] | CMD2[6];
    
    condition[7] = condition[7] | CMD2[7];
    condition[7] <<= 4;
    condition[7] = condition[7] | CMD2[8];
}

void Reversal(){
    int i,j;
    char value = 0x00,Bit = 0x00;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 8;j++){
            Bit = condition[i] & 0x01;
            printf("%d",Bit);
            value <<= 1;
            value = value | Bit;
            condition[i] >>= 1;
            Bit = 0;
        }
        condition[i] = value;
    }
}

/*void judgement(String uart){
    int data[2];
    data[0] = receive[5] - '0';
    data[1] = receive[6] - '0';

    if(uart == "SWTH"){
        Switch(data[1]);
    }else if(uart == "RUNI"){
        RunInit();
    }else if(uart == "MODE"){
        mode = data[1];
        Mode(data[1]);
    }else if(uart == "WIND"){
        Wind(data[1]);
    }else if(uart == "SWEP"){
        Sweep(data[1]);
    }else if(uart == "SLEP"){
        Sleep(data[1]);
    }else if(uart == "SPTM"){
        SleepTime(data[0] * 10 + data[1]);
    }else if(uart == "TEMP"){
        temp = data[0] * 10 + data[1];
        Temp(data[0] * 10 + data[1]);
    }else if(uart == "SUPR"){
        Super(data[1]);
    }else if(uart == "LGHT"){
        Light(data[1]);
    }else if(uart == "HLTH"){
        Health(data[1]);
    }else if(uart == "HEAT"){
        Heat(data[1]);
    }else if(uart == "DSPY"){
        Display(data[1]);
    }else{
        Serial.print("error");
    }
}
*/
int main()
{
	int i;
    process();
    /*for(i=0;i<8;i++)
    {
    	printf("%d\n",condition[i]);
    }*/
   	return 0;
}
