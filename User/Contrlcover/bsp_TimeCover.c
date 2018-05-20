#include "bsp_TimeCover.h" 
#include "bsp_usart.h"
 
static void CONTROL2_DRV8825_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(DrEN_GPIO_CLK | DrM0_GPIO_CLK | DrM1_GPIO_CLK | DrM2_GPIO_CLK, ENABLE);	
	RCC_APB2PeriphClockCmd(DrDIR_GPIO_CLK , ENABLE);


    /*ѡ��Ҫ���Ƶ�EN����*/
	GPIO_InitStructure.GPIO_Pin = DrEN_GPIO_PIN;	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(DrEN_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�M0����*/
	GPIO_InitStructure.GPIO_Pin = DrM0_GPIO_PIN;
	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(DrM0_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�M1����*/
	GPIO_InitStructure.GPIO_Pin = DrM1_GPIO_PIN;
	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(DrM1_GPIO_PORT, &GPIO_InitStructure);

	/*ѡ��Ҫ���Ƶ�M2����*/
	GPIO_InitStructure.GPIO_Pin = DrM2_GPIO_PIN;
	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(DrM2_GPIO_PORT, &GPIO_InitStructure);



	/*ѡ��Ҫ���Ƶ�DIR����*/
	GPIO_InitStructure.GPIO_Pin = DrDIR_GPIO_PIN;
	/*���ÿ⺯������ʼ��GPIOF*/
	GPIO_Init(DrDIR_GPIO_PORT, &GPIO_InitStructure);
	
	/* EN */
	GPIO_SetBits(DrEN_GPIO_PORT, DrEN_GPIO_PIN);		
  /* M0=0 */
	GPIO_ResetBits(DrM0_GPIO_PORT, DrM0_GPIO_PIN);	   
	/* M1=0 */
	GPIO_ResetBits(DrM1_GPIO_PORT, DrM1_GPIO_PIN);
	/* M2=0 */
	GPIO_ResetBits(DrM2_GPIO_PORT, DrM2_GPIO_PIN);

	/* DIR=1 */
	GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);

}



static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	
	// ����Ƚ�ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(COVER_TIM_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = COVER_TIM_CH2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(COVER_TIM_CH2_PORT, &GPIO_InitStructure);
}

#if 1
// �ж����ȼ�����
static void COVER_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ3
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = COVER_TIM_IRQ ;	
		// ���������ȼ�Ϊ 2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	  // ������ռ���ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
#endif

static void COVER_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   //ʱ���ṹ��
    TIM_OCInitTypeDef  TIM_OCInitStructure;           //����ȽϽṹ���ʼ��
		
    // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    COVER_TIM_APBxClock_FUN(COVER_TIM_CLK, ENABLE);
	
    // �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = COVER_TIM_Period;	

	// ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler = COVER_TIM_Prescaler;
	
    // ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		
	// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
			
	// ��ʼ����ʱ��
    TIM_TimeBaseInit(COVER_TIM, &TIM_TimeBaseStructure);


	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	// ����ռ�ձȴ�С
	TIM_OCInitStructure.TIM_Pulse = COVER_TIM_Period/2;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	// ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	
	//ʹ��TIM1_CH2Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//ʹ��TIM2Ԥװ�ؼĴ���
    TIM_ARRPreloadConfig(TIM2, ENABLE); 
	//�����ж�Դ��ֻ�����ʱ���ж�
    TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Regular);
		
	// ����������жϱ�־λ
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	  
	// �����������ж�
    TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
		
	// ʹ�ܼ�����
    TIM_Cmd(TIM2, DISABLE);	
    TIM_CtrlPWMOutputs(TIM2, DISABLE);
}
	
void Cover_TIM_Init(void)
{
	CONTROL2_DRV8825_GPIO_Config();
	ADVANCE_TIM_GPIO_Config();	
	COVER_TIM_Mode_Config();
	COVER_TIM_NVIC_Config();
	 //Timer2_Configuration();
}

void ControlCover(FunctionalState NewState)
{ 
	if (NewState == DISABLE)
	{
		//ʹ�ܶ�ʱ��	
		TIM_Cmd(TIM2, DISABLE);
		TIM_CtrlPWMOutputs(TIM2, DISABLE);
		/* EN */
		GPIO_SetBits(DrEN_GPIO_PORT, DrEN_GPIO_PIN);
		//printf("TIM is disable!\n");
	}
	else
	{
		//ʹ�ܶ�ʱ��	
		TIM_Cmd(TIM2, ENABLE);
		TIM_CtrlPWMOutputs(TIM2, ENABLE);
		/* EN */
	   GPIO_ResetBits(DrEN_GPIO_PORT, DrEN_GPIO_PIN);
		//printf("TIM is able!\n");
	}
}

//uSpeedCoverOneΪ�ߵ�ƽռ�ձ�
void SetSpeedCoverPulse(u16 uSpeedCoverOne)
{
	
    TIM_SetCompare1(COVER_TIM, uSpeedCoverOne);
	
}

void SetSpeedCoverMoter(u16 SpeedMoter)
{
	//���ö�ʱ����װֵ	
    TIM_SetAutoreload(TIM2, SpeedMoter);
    //����ռ�ձ�Ϊ50%	
    TIM_SetCompare1(TIM2, SpeedMoter>>1);
}

//�����ٶ�
void SetSpeedCover(u16 uSetSpeed)
{
	SetSpeedCoverMoter(10000/uSetSpeed);
}

#if 0
void Timer2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    TIM_TimeBaseStructure.TIM_Period = 1000-1;             
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;            
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    TIM_ARRPreloadConfig(TIM2, DISABLE);
    TIM_ClearITPendingBit(TIM2,  TIM_IT_Update); 
    TIM_ITConfig(TIM2,  TIM_IT_Update, ENABLE);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_Pulse = 500-1;     
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
    
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  
    TIM_CtrlPWMOutputs(TIM2,ENABLE);       
    TIM_Cmd(TIM2, ENABLE);
}
#endif
