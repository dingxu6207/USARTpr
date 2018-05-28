#include "Exti44E.h"



 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* �����ж�Դ��PB0 */
  NVIC_InitStructure.NVIC_IRQChannel = RAEAST_INT_EXTI_IRQ;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* �����ж�Դ��PB1������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = RAWEST_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  /* �����ж�Դ��PB3������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = DECUP_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);

  
  /* �����ж�Դ��PB4������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = DECDOWN_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_44E_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); 
	
	RCC_APB2PeriphClockCmd(RAEAST_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(RAWEST_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(DECUP_INT_GPIO_CLK,ENABLE); 
	RCC_APB2PeriphClockCmd(DECDOWN_INT_GPIO_CLK,ENABLE);
												
	/* ���� NVIC �ж�*/
	NVIC_Configuration();
	
/*--------------------------PB0-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = RAEAST_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(RAEAST_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(RAEAST_INT_EXTI_PORTSOURCE, RAEAST_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = RAEAST_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �����ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------PB1����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = RAWEST_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(RAWEST_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(RAWEST_INT_EXTI_PORTSOURCE, RAWEST_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = RAWEST_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �½����ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


  /*--------------------------PB3����-----------------------------*/
/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = DECUP_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DECUP_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(DECUP_INT_EXTI_PORTSOURCE, DECUP_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = DECUP_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �����ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /*--------------------------PB4����-----------------------------*/
  /* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = DECDOWN_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DECDOWN_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(DECDOWN_INT_EXTI_PORTSOURCE, DECDOWN_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = DECDOWN_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �����ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

