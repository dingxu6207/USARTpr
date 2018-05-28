#ifndef __Exti44E_H
#define __Exti44E_H

#include "stm32f10x.h"

#define RAEAST_INT_GPIO_PORT         GPIOB
#define RAEAST_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define RAEAST_INT_GPIO_PIN          GPIO_Pin_0
#define RAEAST_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define RAEAST_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define RAEAST_INT_EXTI_LINE         EXTI_Line0
#define RAEAST_INT_EXTI_IRQ          EXTI0_IRQn

#define RAEAST_IRQHandler            EXTI0_IRQHandler


#define RAWEST_INT_GPIO_PORT         GPIOB
#define RAWEST_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define RAWEST_INT_GPIO_PIN          GPIO_Pin_1
#define RAWEST_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define RAWEST_INT_EXTI_PINSOURCE    GPIO_PinSource1
#define RAWEST_INT_EXTI_LINE         EXTI_Line1
#define RAWEST_INT_EXTI_IRQ          EXTI1_IRQn

#define RAWEST_IRQHandler            EXTI1_IRQHandler


#define DECUP_INT_GPIO_PORT         GPIOB
#define DECUP_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define DECUP_INT_GPIO_PIN          GPIO_Pin_3
#define DECUP_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define DECUP_INT_EXTI_PINSOURCE    GPIO_PinSource3
#define DECUP_INT_EXTI_LINE         EXTI_Line3
#define DECUP_INT_EXTI_IRQ          EXTI3_IRQn

#define DECUP_IRQHandler            EXTI3_IRQHandler


#define DECDOWN_INT_GPIO_PORT         GPIOB
#define DECDOWN_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define DECDOWN_INT_GPIO_PIN          GPIO_Pin_4
#define DECDOWN_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define DECDOWN_INT_EXTI_PINSOURCE    GPIO_PinSource4
#define DECDOWN_INT_EXTI_LINE         EXTI_Line4
#define DECDOWN_INT_EXTI_IRQ          EXTI4_IRQn

#define DECDOWN_IRQHandler            EXTI4_IRQHandler


void EXTI_44E_Config(void);

#endif

