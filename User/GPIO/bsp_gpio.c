#include "./GPIO/bsp_gpio.h"   

void GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( GPIO1_GPIO_CLK|
	                           GPIO2_GPIO_CLK|
	                           GPIO3_GPIO_CLK|
														 GPIO4_GPIO_CLK|
														 GPIO5_GPIO_CLK, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_InitStructure.GPIO_Pin = GPIO1_PIN;	
		GPIO_Init(GPIO1_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO2_PIN;	
    GPIO_Init(GPIO2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO3_PIN;	
    GPIO_Init(GPIO3_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = GPIO4_PIN;	
    GPIO_Init(GPIO4_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO5_PIN;	
    GPIO_Init(GPIO5_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_ResetBits(GPIO1_GPIO_PORT,GPIO1_PIN);
		GPIO_ResetBits(GPIO2_GPIO_PORT,GPIO2_PIN);
		GPIO_ResetBits(GPIO3_GPIO_PORT,GPIO3_PIN);
		GPIO_ResetBits(GPIO4_GPIO_PORT,GPIO4_PIN);
		GPIO_ResetBits(GPIO5_GPIO_PORT,GPIO5_PIN);
		
}
/*********************************************END OF FILE**********************/
