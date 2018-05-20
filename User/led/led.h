#ifndef		__LED_H
#define		__LED_H

#include "stm32f10x.h"

#define LED_GPIO_PORT    	GPIOA                       /* GPIO端口 */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED_GPIO_PIN		GPIO_Pin_1			        /* 连接到led时钟线的GPIO */
void LEDINIT(void);
#endif
