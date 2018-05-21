#include "led.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h" 

void LEDINIT(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 
     /*开启LED相关的GPIO外设时钟*/
	 RCC_APB2PeriphClockCmd( LED_GPIO_CLK | LED_GPIO_CLK, ENABLE);

     /*选择要控制的GPIO引脚*/
	 GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
	
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);			
}

extern u8 uCountStep ;
extern u8 uCountStep1;

void GOTO ( int *ra_step, int *dec_step)  //按计算结果移动步进电机
{
     u8 ra_overflows = 8, dec_overflows = 8;

	ControlMotor(ENABLE);
	ControlCover(ENABLE);
    if((*ra_step) == 0 )	//到位了就切换到RA正常速度跟踪
    {		
		ControlMotor(DISABLE);
    }

     if((*dec_step) == 0 )	//到位了DEC停止
    {
		ControlCover(DISABLE);
    }

    if(uCountStep > ra_overflows) //RA轴运动标志置位及按运动情况修改记步数据
    {
        uCountStep = 1;
        if ( (*ra_step) > 0 )
        {
            (*ra_step)--;
			GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
        }
        if ( (*ra_step) < 0 )
        {
            (*ra_step)++;
            GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
        }
    }

   if(uCountStep1 > dec_overflows) //DEC轴运动标志置位及按运动情况修改记步数据
   {
        uCountStep1 = 1;
        if ( (*dec_step) > 0 )
        {
            (*dec_step)--;
             GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
        }
        if ( (*dec_step) < 0 )
        {
            (*dec_step)++;
            GPIO_ResetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
        }
   }
	
}
