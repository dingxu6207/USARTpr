#ifndef		__LED_H
#define		__LED_H

#include "stm32f10x.h"

#define LED_GPIO_PORT    	GPIOA                       /* GPIO�˿� */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LED_GPIO_PIN		GPIO_Pin_1			        /* ���ӵ�ledʱ���ߵ�GPIO */
void LEDINIT(void);
#endif
