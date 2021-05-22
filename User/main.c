#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "lcd.h"
#include "GBK_LibDrive.h"	
#include "./adc/bsp_adc.h"
#include "stm32f4xx_it.h"
#include "./tim/bsp_advance_tim.h"
#include "./GPIO/bsp_gpio.h"


//电容部分
extern uint16_t IC2Value;
extern uint16_t IC1Value;
extern float DutyCycle;
extern float Frequency;
float  ln2 = 0.69314718;
double c = 0;
double c_t = 0;


//电阻部分
#define gear_default		4 
#define R1_default			50*1000
#define v_default				4.9
extern __IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];	 
float ADC_ConvertedValueLocal[RHEOSTAT_NOFCHANEL]={0}; 
float R1 = 50;
float v =4.9;
float Rx = 0;
char gear = 5;


int times = 0;


u8 x=0;
u8 lcd_id[12];				//存放LCD ID字符串


void Show_R(double Resistor,char range);
void Show_C(double Capacity,char range);
void Mea_R(void);
void Mea_C(void);
void GPI_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Change_range(void);
void switch_5(void);	//电阻电容切换
void switch_4(void);	//电阻最小挡
void switch_3(void);	
void switch_2(void);
void switch_1(void);	//电阻最大挡
void get_F_C(void);
	
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	POINT_COLOR=RED;      //画笔颜色：红色
	GBK_Lib_Init();       //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化） 		 	

	GPIO_Config();
	Rheostat_Init();
	TIMx_Configuration();

	
	
	while(1) 
	{	
		if(times % 2 == 0) switch_5();
		delay_ms(100);
		get_F_C();
		delay_ms(10);
		Draw_Font24B(24,24,BLUE,"简易电阻电容测量");
		if(DutyCycle == 0 || DutyCycle == 100 || DutyCycle == 80) 
		{
			get_F_C();
			delay_ms(10);
			if(DutyCycle == 0 || DutyCycle == 100 || DutyCycle == 80)
			{
				Draw_Font24B(0,80,BLACK,"R:");
				switch_1();
				Mea_R();
				Draw_Font24B(0,120,RED,"             ");
			}
		}else
		{
			get_F_C();
			delay_ms(10);
			if(DutyCycle != 0 && DutyCycle != 100)
			{
				Draw_Font24B(0,120,BLACK,"C:");	
				Mea_C();
				Draw_Font24B(0,80,RED,"             ");
			}
		}
		printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
		printf("占空比：%0.2f%%   频率：%0.2fHz\n",DutyCycle,Frequency);	
		delay_ms(1000);
		times++;
		if(times == 1000) times =0;
		
	} 
}

/*range 0: 0~9;
				1: 10~99;
				2: 100~999;
				3: 1k~9.999k
				4: 10k~99.999k
				5: 100k~999.999k 
*/
void Show_R(double Resistor,char range)
{
	int R;
	unsigned char  R_arry[5] = {0x01,0x01,0x01,0x01,0x01};
	unsigned char  R_arry_temp[4] = {0};
	unsigned char  temp;
	unsigned char  cnt;
	unsigned char  point_loc;
	unsigned char  i;
	unsigned char mutiple;
	
	if(range == 0||range == 1||range == 2)
	{
		//判断量程
		if(range == 0) 
		{
			mutiple = 100;
			cnt = 2;
			temp = (int)(Resistor);
		}
		if(range == 1) 
		{
			mutiple = 10;
			cnt = 1;
			temp =	(int)(Resistor/10);
		}
		if(range == 2) 
		{
			mutiple = 1;
			cnt = 0;
			temp =	(int)(Resistor/100);
		}
		//判断第一位
		if(temp >=2)
		{
			R = (int)(Resistor * mutiple);
			point_loc = 4-cnt;
		}else
    {
			R = (int)(Resistor * mutiple * 10);
			point_loc = 4-(cnt+1);
		}
		
		R_arry_temp[0] = R/1000+0x30;
		R_arry_temp[1] = R/100%10+0x30;
		R_arry_temp[2] = R/10%10+0x30;
		R_arry_temp[3] = R%10+0x30;
		unsigned char  k = 0;
		for(i = 0; i < 5; i++)
		{
			if(i != point_loc)
			{
				R_arry[i] =  R_arry_temp[k];
				k++;
			}else if(point_loc <= 3)
			{
				R_arry[i] = '.';
			}				
		}		
		Draw_Font24B(48,80,RED,R_arry);
	  Draw_Font24B(48+16*4,80,RED," Ω");
	}
	if(range == 3||range == 4||range == 5)
	{
				//判断量程
		if(range == 3) 
		{
			mutiple = 1;
			cnt = 3;
			temp = (int)(Resistor/1000);
		}
		if(range == 4) 
		{
			mutiple = 10;
			cnt = 2;
			temp =	(int)(Resistor/10000);
		}
		if(range == 5) 
		{
			mutiple = 100;
			cnt = 1;
			temp =	(int)(Resistor/100000);
		}
		//判断第一位
		if(temp >= 2)
		{
			R = (int)(Resistor / (mutiple * 10));
			point_loc = 4-(cnt-1);
		}else
    {
			R = (int)(Resistor / mutiple);
			point_loc = 4-cnt;
		}
		
		R_arry_temp[0] = R/1000+0x30;
		R_arry_temp[1] = R/100%10+0x30;
		R_arry_temp[2] = R/10%10+0x30;
		R_arry_temp[3] = R%10+0x30;
		unsigned char  k = 0;
		for(i = 0; i < 5; i++)
		{
			if(i != point_loc)
			{
				R_arry[i] =  R_arry_temp[k];
				k++;
			}else if(point_loc <= 3)
			{
				R_arry[i] = '.';
			}				
		}		
		Draw_Font24B(48,80,RED,R_arry);
	  Draw_Font24B(48+16*4,80,RED,"KΩ");
	}	
}


void Show_C(double Capacity,char range)
{
	int C;
	unsigned char  C_arry[5] = {0x01,0x01,0x01,0x01,0x01};
	unsigned char  C_arry_temp[4] = {0};
	unsigned char  temp;
	unsigned char  cnt;
	unsigned char  point_loc;
	unsigned char  i;
	unsigned char mutiple;
	
	if(range == 0||range == 1||range == 2)
	{
		//判断量程
		if(range == 0) 
		{
			mutiple = 100;
			cnt = 2;
			temp = (int)(Capacity);
		}
		if(range == 1) 
		{
			mutiple = 10;
			cnt = 1;
			temp =	(int)(Capacity/10);
		}
		if(range == 2) 
		{
			mutiple = 1;
			cnt = 0;
			temp =	(int)(Capacity/100);
		}
		//判断第一位
		if(temp >=2)
		{
			C = (int)(Capacity * mutiple);
			point_loc = 4-cnt;
		}else
    {
			C = (int)(Capacity * mutiple * 10);
			point_loc = 4-(cnt+1);
		}
		
		C_arry_temp[0] = C/1000+0x30;
		C_arry_temp[1] = C/100%10+0x30;
		C_arry_temp[2] = C/10%10+0x30;
		C_arry_temp[3] = C%10+0x30;
		unsigned char  k = 0;
		for(i = 0; i < 5; i++)
		{
			if(i != point_loc)
			{
				C_arry[i] =  C_arry_temp[k];
				k++;
			}else if(point_loc <= 3)
			{
				C_arry[i] = '.';
			}				
		}		
		Draw_Font24B(48,120,RED,C_arry);
		Draw_Font24B(48+16*4,120,RED,"nf");
	}
	if(range == 3||range == 4||range == 5)
	{
				//判断量程
		if(range == 3) 
		{
			mutiple = 1;
			cnt = 3;
			temp = (int)(Capacity/1000);
		}
		if(range == 4) 
		{
			mutiple = 10;
			cnt = 2;
			temp =	(int)(Capacity/10000);
		}
		if(range == 5) 
		{
			mutiple = 100;
			cnt = 1;
			temp =	(int)(Capacity/100000);
		}
		//判断第一位
		if(temp >= 2)
		{
			C = (int)(Capacity / (mutiple * 10));
			point_loc = 4-(cnt-1);
		}else
    {
			C = (int)(Capacity / mutiple);
			point_loc = 4-cnt;
		}
		
		C_arry_temp[0] = C/1000+0x30;
		C_arry_temp[1] = C/100%10+0x30;
		C_arry_temp[2] = C/10%10+0x30;
		C_arry_temp[3] = C%10+0x30;
		unsigned char  k = 0;
		for(i = 0; i < 5; i++)
		{
			if(i != point_loc)
			{
				C_arry[i] =  C_arry_temp[k];
				k++;
			}else if(point_loc <= 3)
			{
				C_arry[i] = '.';
			}				
		}		
		Draw_Font24B(48,120,RED,C_arry);
	  Draw_Font24B(48+16*4,120,RED,"uf");
	}	

}


void Mea_R(void)
{
	ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
	
	Change_range();
	
	ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
	unsigned char i = 0;
	float Rx_del = 0;
	for(i = 0; i < 100; i++)
	{
		Rx = R1*ADC_ConvertedValueLocal[2]/(5-ADC_ConvertedValueLocal[2]);
		Rx_del += Rx;
	}
	Rx = Rx_del/100;
	if(gear == 4)
	{
		if(Rx > 10000 && Rx <= 12000) Rx -= 2500;
		if(Rx > 12000 && Rx <= 43000) Rx -= 2000;
		if(Rx > 43000 && Rx <= 57000) Rx -= 1000;
		if(Rx > 57000 && Rx <= 72000) Rx += 2000;
		if(Rx > 73000 && Rx <= 100000) Rx += 10000;
	}
	
//	Rx = R1*ADC_ConvertedValueLocal[2]/(5-ADC_ConvertedValueLocal[2]);
//	if(gear == 4)
//	{
//		if(Rx > 10000 && Rx <= 12000) Rx -= 2500;
//		if(Rx > 12000 && Rx <= 43000) Rx -= 2000;
//		if(Rx > 43000 && Rx <= 57000) Rx -= 1000;
//		if(Rx > 57000 && Rx <= 70000) Rx += 2000;
//		if(Rx > 70000 && Rx <= 100000) Rx += 10000;
//	}
	Show_R(Rx,gear);
//	Show_R(Rx,2);
}
void Mea_C(void)
{
	char gear_c = 0;
	c = (float)((1/(Frequency*1240000*ln2))*10000000000);
//	if(Frequency >= 0 && Frequency < 10) gear_c = 0;
//	if(Frequency >= 10 && Frequency < 100) gear_c = 1;
//	if(Frequency >= 100 && Frequency < 1000) gear_c = 2;
//	if(Frequency >= 1000 && Frequency < 10000) gear_c = 3;
//	if(Frequency >= 10000 && Frequency < 100000) gear_c = 4;
	
	if(c >= 0 && c < 10) gear_c = 0;
	if(c >= 10 && c < 100) gear_c = 1;
	if(c >= 100 && c < 1000) gear_c = 2;
	if(c >= 1000 && c < 10000) gear_c = 3;
	if(c >= 10000 && c < 100000) gear_c = 4;
	Show_C(c,gear_c);
//	Show_C(200,2);
}

void Change_range(void)
{
	float Threshold = 0.8300;
	delay_ms(10);
	ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
	
	if(ADC_ConvertedValueLocal[2] > 3.25f || (ADC_ConvertedValueLocal[2] > 2.6f && ADC_ConvertedValueLocal[2] < 2.75f))
	{
		switch_1();
		delay_ms(10);
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
	}
	
	if(ADC_ConvertedValueLocal[2] < Threshold)
	{
		switch_1();
		unsigned char i = 0;
		
		while(ADC_ConvertedValueLocal[2] < Threshold)
		{
			switch(i)
			{
				case 0: switch_1();
								break;
				case 1: switch_2();
								break;
				case 2: switch_3();
								break;
				case 3: switch_4();
								break;
			}
			i++;
			if(i >= 4) i = 0;
			delay_ms(10);
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
		}
	}
}

void switch_5(void)
{
	GPIO1_OFF
	GPIO2_OFF
	GPIO3_OFF
	GPIO4_OFF
	GPIO5_ON
}

void switch_4(void)
{
	gear = gear_default-3;
	R1 = R1_default/1000;
	GPIO1_OFF
	GPIO2_OFF
	GPIO3_OFF
	GPIO5_OFF
	GPIO4_ON
}
void switch_3(void)
{
	gear = gear_default-2;
	R1 = R1_default/100;
	GPIO1_OFF
	GPIO2_OFF
	GPIO4_OFF
	GPIO5_OFF
	GPIO3_ON
}
void switch_2(void)
{
	gear = gear_default-1;
	R1 = R1_default/10;
	GPIO1_OFF
	GPIO3_OFF
	GPIO4_OFF
	GPIO5_OFF
	GPIO2_ON
}

void switch_1(void)
{
	gear = gear_default;
	R1 = R1_default;
	GPIO2_OFF
	GPIO3_OFF
	GPIO4_OFF
	GPIO5_OFF
	GPIO1_ON
}

void get_F_C(void)
{
	if (IC1Value != 0)
	{
		/* 占空比计算 */
		DutyCycle = (float)(IC2Value * 100) / IC1Value;

		/* 频率计算 */
		Frequency = 168000000/1680/(float)IC1Value;
	}
	else
	{
		DutyCycle = 0;
		Frequency = 0;
	}

}


