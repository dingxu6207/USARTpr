#ifndef		__LED_H
#define		__LED_H

#include "stm32f10x.h"

#define LED_GPIO_PORT    	GPIOA                       /* GPIO端口 */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LED_GPIO_PIN		GPIO_Pin_1			        /* 连接到led时钟线的GPIO */
void LEDINIT(void);


#define RA_STP_ANGLE		10		//RA步进电机一个步进时赤道仪的转角（角秒）360*3600/648/200 = 10
#define DEC_STP_ANGLE		10		//DEC步进电机一个步进时赤道仪的转角（角秒）10


void GOTO ( int *ra_step, int *dec_step);  //按计算结果移动步进电机

#endif
