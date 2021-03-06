
// 基本定时器TIMx,x[1]定时初始化函数

#include "bsp_TiMbase.h" 
#include "bsp_usart.h"




static void ADVANCE_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
	
	// 输出比较通道 GPIO 初始化
	RCC_APB2PeriphClockCmd(ADVANCE_TIM_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = ADVANCE_TIM_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(ADVANCE_TIM_CH1_PORT, &GPIO_InitStructure);
}

static void CONTROL_DRV8825_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);
 
	RCC_APB2PeriphClockCmd(EN_GPIO_CLK | M0_GPIO_CLK | M1_GPIO_CLK | M2_GPIO_CLK, ENABLE);	
	RCC_APB2PeriphClockCmd( DIR_GPIO_CLK , ENABLE);
	RCC_APB2PeriphClockCmd( LED0_GPIO_CLK , ENABLE);
	//RCC_APB2PeriphClockCmd( SLF_GPIO_CLK , ENABLE);

    /*选择要控制的EN引脚*/
	GPIO_InitStructure.GPIO_Pin = EN_GPIO_PIN;	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*调用库函数，初始化GPIO*/
	GPIO_Init(EN_GPIO_PORT, &GPIO_InitStructure);

	/*选择要控制的M0引脚*/
	GPIO_InitStructure.GPIO_Pin = M0_GPIO_PIN;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(M0_GPIO_PORT, &GPIO_InitStructure);

	/*选择要控制的M1引脚*/
	GPIO_InitStructure.GPIO_Pin = M1_GPIO_PIN;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(M1_GPIO_PORT, &GPIO_InitStructure);

	/*选择要控制的M2引脚*/
	GPIO_InitStructure.GPIO_Pin = M2_GPIO_PIN;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(M2_GPIO_PORT, &GPIO_InitStructure);

   
	/*选择要控制的RST引脚*/
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
	
     #if 0
	/*选择要控制的SLF引脚*/
	GPIO_InitStructure.GPIO_Pin = SLF_GPIO_PIN;
	/*调用库函数，初始化GPIO*/
	GPIO_Init(SLF_GPIO_PORT, &GPIO_InitStructure);
	#endif

	/*选择要控制的DIR引脚*/
	GPIO_InitStructure.GPIO_Pin = DIR_GPIO_PIN;
	/*调用库函数，初始化GPIOF*/
	GPIO_Init(DIR_GPIO_PORT, &GPIO_InitStructure);
	
	/* EN */
	GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN);		
  /* M0=1 */
	GPIO_SetBits(M0_GPIO_PORT, M0_GPIO_PIN);	   
	/* M1=1 */
	GPIO_SetBits(M1_GPIO_PORT, M1_GPIO_PIN);
	/* M2=0 */
	GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);

	/* DIR=1 */
	GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);

	#if 0
	/* SLF=1 */
	GPIO_SetBits(SLF_GPIO_PORT, SLF_GPIO_PIN);
	#endif
	/* LED0=0 */
	GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);	
	
	
}
	

// 中断优先级配置
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            都有
 *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
 *  TIM_Period               都有
 *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */


static void BASIC_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   //时基结构体
    TIM_OCInitTypeDef  TIM_OCInitStructure;           //输出比较结构体初始化

	//时基结构体初始化
	//TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
		
    // 开启定时器时钟,即内部时钟CK_INT=72M
    BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
	
    // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;	

	// 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;
	
    // 时钟分频因子 ，基本定时器没有，不用管
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		
	// 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		
	// 重复计数器的值，基本定时器没有，不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	// 初始化定时器
  	TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);


	/*--------------------输出比较结构体初始化-------------------*/	
	// 配置为PWM模式2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 互补输出禁能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	// 设置占空比大小
	TIM_OCInitStructure.TIM_Pulse = BASIC_TIM_Period/2;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	// 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	//使能TIM1_CH1预装载寄存器
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//使能TIM1预装载寄存器
    TIM_ARRPreloadConfig(TIM1, ENABLE); 
	//设置中断源，只有溢出时才中断
    TIM_UpdateRequestConfig(TIM1, TIM_UpdateSource_Regular);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(BASIC_TIM, DISABLE);	

	  TIM_CtrlPWMOutputs(TIM1, DISABLE);
}

void BASIC_TIM_Init(void)
{
    CONTROL_DRV8825_GPIO_Config();
	ADVANCE_TIM_GPIO_Config();
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();		
}

void ControlMotor(FunctionalState NewState)
{ 
	if (NewState == DISABLE)
	{
		//使能定时器	      
    TIM_Cmd(BASIC_TIM, DISABLE);
		TIM_CtrlPWMOutputs(BASIC_TIM, DISABLE); //禁止输出
		//定时器关闭后再关闭使能
		GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN); //DRV8825使能信号
		//printf("TIM is disable!\n");
	}
	else
	{
		//使能定时器			
        TIM_Cmd(BASIC_TIM, ENABLE);
		TIM_CtrlPWMOutputs(BASIC_TIM, ENABLE); //输出			
		//在控制函数中启动使能，然后再开启定时器
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN); //DRV8825使能信号
		//printf("TIM is able!\n");
	}
}


void SetSpeedMoter(u16 SpeedMoter)
{
	//设置定时器重装值	
    TIM_SetAutoreload(BASIC_TIM, SpeedMoter);
    //设置占空比为50%	
    TIM_SetCompare1(BASIC_TIM, SpeedMoter>>1);
}

//设置速度
void SetSpeed(u16 uSetSpeed)
{
	SetSpeedMoter(10000/uSetSpeed);
}
/*********************************************END OF FILE**********************/
