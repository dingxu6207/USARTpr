#include "Exti44E.h"



 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* 配置中断源：PB0 */
  NVIC_InitStructure.NVIC_IRQChannel = RAEAST_INT_EXTI_IRQ;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* 配置中断源：PB1，其他使用上面相关配置 */  
  NVIC_InitStructure.NVIC_IRQChannel = RAWEST_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  /* 配置中断源：PB3，其他使用上面相关配置 */  
  NVIC_InitStructure.NVIC_IRQChannel = DECUP_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  
  /* 配置中断源：PB4，其他使用上面相关配置 */  
  NVIC_InitStructure.NVIC_IRQChannel = DECDOWN_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_44E_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); 
	
	RCC_APB2PeriphClockCmd(RAEAST_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(RAWEST_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(DECUP_INT_GPIO_CLK,ENABLE); 
	RCC_APB2PeriphClockCmd(DECDOWN_INT_GPIO_CLK,ENABLE);
												
	/* 配置 NVIC 中断*/
	NVIC_Configuration();
	
/*--------------------------PB0-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = RAEAST_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(RAEAST_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(RAEAST_INT_EXTI_PORTSOURCE, RAEAST_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = RAEAST_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 边沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------PB1配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = RAWEST_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(RAWEST_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(RAWEST_INT_EXTI_PORTSOURCE, RAWEST_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = RAWEST_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


  /*--------------------------PB3配置-----------------------------*/
/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = DECUP_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DECUP_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(DECUP_INT_EXTI_PORTSOURCE, DECUP_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = DECUP_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 边沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /*--------------------------PB4配置-----------------------------*/
  /* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = DECDOWN_INT_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DECDOWN_INT_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(DECDOWN_INT_EXTI_PORTSOURCE, DECDOWN_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = DECDOWN_INT_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 边沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

