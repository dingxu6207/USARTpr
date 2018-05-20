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

extern int uCountStep ;
extern int uCountStep1;

void GOTO ( int *ra_step, int *dec_step)  //按计算结果移动步进电机
{
     u16 ra_overflows = 10, dec_overflows = 10;

	ControlMotor(ENABLE);
	ControlCover(ENABLE);
    if((*ra_step) == 0 )	//到位了就切换到RA正常速度跟踪
    {
		ControlCover(DISABLE);
    }

     if((*dec_step) == 0 )	//到位了就切换到RA正常速度跟踪
    {
		ControlCover(DISABLE);
    }

    if(uCountStep > ra_overflows) //RA轴运动标志置位及按运动情况修改记步数据
    {
        uCountStep = 1;
        if ( (*ra_step) > 0 )
        {
            (*ra_step)--;
        }
        if ( (*ra_step) < 0 )
        {
            (*ra_step)++;
        }
    }

   if(uCountStep1 > dec_overflows) //DEC轴运动标志置位及按运动情况修改记步数据
    {
        uCountStep1 = 1;
        if ( (*dec_step) > 0 )
        {
            (*dec_step)--;
        }
        if ( (*dec_step) < 0 )
        {
            (*dec_step)++;
        }
    }
	
}
