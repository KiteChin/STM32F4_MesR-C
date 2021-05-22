#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f4xx.h"

//引脚定义
/*******************************************************/
//R 红色灯
#define GPIO1_PIN                  GPIO_Pin_13                 
#define GPIO1_GPIO_PORT            GPIOG                      
#define GPIO1_GPIO_CLK             RCC_AHB1Periph_GPIOF

//G 绿色灯
#define GPIO2_PIN                  GPIO_Pin_15                 
#define GPIO2_GPIO_PORT            GPIOG                      
#define GPIO2_GPIO_CLK             RCC_AHB1Periph_GPIOF

//B 蓝色灯
#define GPIO3_PIN                  GPIO_Pin_4                 
#define GPIO3_GPIO_PORT            GPIOB                       
#define GPIO3_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define GPIO4_PIN                  GPIO_Pin_6                
#define GPIO4_GPIO_PORT            GPIOB                       
#define GPIO4_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define GPIO5_PIN                  GPIO_Pin_8                 
#define GPIO5_GPIO_PORT            GPIOB                   
#define GPIO5_GPIO_CLK             RCC_AHB1Periph_GPIOF




//#define GPIO1_PIN                  GPIO_Pin_7                 
//#define GPIO1_GPIO_PORT            GPIOE                      
//#define GPIO1_GPIO_CLK             RCC_AHB1Periph_GPIOF

////G 绿色灯
//#define GPIO2_PIN                  GPIO_Pin_9                 
//#define GPIO2_GPIO_PORT            GPIOE                      
//#define GPIO2_GPIO_CLK             RCC_AHB1Periph_GPIOF

////B 蓝色灯
//#define GPIO3_PIN                  GPIO_Pin_11                 
//#define GPIO3_GPIO_PORT            GPIOE                       
//#define GPIO3_GPIO_CLK             RCC_AHB1Periph_GPIOF

//#define GPIO4_PIN                  GPIO_Pin_13                
//#define GPIO4_GPIO_PORT            GPIOE                       
//#define GPIO4_GPIO_CLK             RCC_AHB1Periph_GPIOF

//#define GPIO5_PIN                  GPIO_Pin_15
//#define GPIO5_GPIO_PORT            GPIOE                   
//#define GPIO5_GPIO_CLK             RCC_AHB1Periph_GPIOF




#define ON  0
#define OFF 1


//
#define GPIO1_ON				GPIO_SetBits(GPIO1_GPIO_PORT,GPIO1_PIN);
//												delay_ms(10);\
//												GPIO_ResetBits(GPIO1_GPIO_PORT,GPIO1_PIN);
#define GPIO1_OFF				GPIO_ResetBits(GPIO1_GPIO_PORT,GPIO1_PIN);

#define GPIO2_ON				GPIO_SetBits(GPIO2_GPIO_PORT,GPIO2_PIN);
//												delay_ms(10);\
//												GPIO_ResetBits(GPIO2_GPIO_PORT,GPIO2_PIN);
#define GPIO2_OFF				GPIO_ResetBits(GPIO2_GPIO_PORT,GPIO2_PIN);
												
#define GPIO3_ON				GPIO_SetBits(GPIO3_GPIO_PORT,GPIO3_PIN);
//												delay_ms(10);\
//												GPIO_ResetBits(GPIO3_GPIO_PORT,GPIO3_PIN);
#define GPIO3_OFF				GPIO_ResetBits(GPIO3_GPIO_PORT,GPIO3_PIN);
												
#define GPIO4_ON				GPIO_SetBits(GPIO4_GPIO_PORT,GPIO4_PIN);
//												delay_ms(10);\
//												GPIO_ResetBits(GPIO4_GPIO_PORT,GPIO4_PIN);
#define GPIO4_OFF				GPIO_ResetBits(GPIO4_GPIO_PORT,GPIO4_PIN);
												
#define GPIO5_ON				GPIO_SetBits(GPIO5_GPIO_PORT,GPIO5_PIN);
//												delay_ms(10);\
//												GPIO_ResetBits(GPIO5_GPIO_PORT,GPIO5_PIN);
#define GPIO5_OFF				GPIO_ResetBits(GPIO5_GPIO_PORT,GPIO5_PIN);


void GPIO_Config(void);

#endif /* __GPIO_H */
