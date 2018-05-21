#ifndef		__LED_H
#define		__LED_H

#include "stm32f10x.h"

#define LED_GPIO_PORT    	GPIOA                       /* GPIO�˿� */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LED_GPIO_PIN		GPIO_Pin_1			        /* ���ӵ�ledʱ���ߵ�GPIO */
void LEDINIT(void);


#define RA_STP_ANGLE		1		//RA�������һ������ʱ����ǵ�ת�ǣ����룩360*360/648/200 = 1
#define DEC_STP_ANGLE		1		//DEC�������һ������ʱ����ǵ�ת�ǣ����룩1


void GOTO ( int *ra_step, int *dec_step);  //���������ƶ��������

#endif
