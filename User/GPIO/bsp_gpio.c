#include "./GPIO/bsp_gpio.h"   

void GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( GPIO1_GPIO_CLK|
	                           GPIO2_GPIO_CLK|
	                           GPIO3_GPIO_CLK|
														 GPIO4_GPIO_CLK|
														 GPIO5_GPIO_CLK, ENABLE); 

		/*选择要控制的GPIO引脚*/															   
		

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_InitStructure.GPIO_Pin = GPIO1_PIN;	
		GPIO_Init(GPIO1_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO2_PIN;	
    GPIO_Init(GPIO2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择要控制的GPIO引脚*/															   
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
