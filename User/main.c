/**
  ******************************************************************************
  * @file    main.c
  * @author  dingxu
  * @version V1.0
  * @date    2018-05-20
  * @brief   赤道仪
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "dma.h"
#include "led.h"
#include "command.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h" 
#include "stdbool.h"
#include "Exti44E.h"
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
u8 data_receive_buffer[USART_REC_LEN];  //来自于串口DMA输入
int ra_step=0, dec_step=0;
s32 current_pos[2]= {0,0}, target_pos[2]= {0,0};
s32 target_ra=0, target_dec=0;
int main(void)
{	
	//s32 current_pos[2]= {0,0}, target_pos[2]= {0,0};
	u8 decode_state=0;
	bool runflag = false;
	int AddStep = 0;
	//s32 target_ra=0, target_dec=0;
	//int ra_step=0, dec_step=0;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    LEDINIT();
  	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  	USART_Config();
	
	SysTick_Init();
	
	DMA_TX_init((u32)data_receive_buffer, USART_REC_LEN);
    DMA_RX_init((u32)data_receive_buffer, USART_REC_LEN);

    BASIC_TIM_Init();
    Cover_TIM_Init();

    EXTI_44E_Config();
   
	
 	while(1)
	{	
		 if(data_receive_buffer[USART_REC_LEN - 1] == 1)  //DMA收到消息标志
        {
            data_receive_buffer[USART_REC_LEN - 1] = 0; //清理标志

            decode_state = LX200( data_receive_buffer, current_pos, target_pos ); //LX200协议解析

            if(GOTO_CHECK(decode_state) == 0xff) //目标位置齐备
            {
				if(current_pos[0] == 0 && current_pos[1] == 0) //如果是系统刚开始运行，则将第一次的GOTO信息设置为当前位置
                {
                    current_pos[0] = target_pos[0];
                    current_pos[1] = target_pos[1];
                    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
                }
                else  //正常GOTO时，根据目标位置计算步数及方向，根据步数和方向乘以系数得到实际需要的步数和方向
                {
                    target_ra = target_pos[0];
                    target_dec = target_pos[1];
                    ra_step	= RA_STEP_CALCULATE(current_pos[0], target_pos[0], RA_STP_ANGLE );   //计算各轴所需步数和方向，正负号代表方向
                    dec_step = DEC_STEP_CALCULATE(current_pos[1], target_pos[1], DEC_STP_ANGLE );
                    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
									runflag = true;
									      
                }
            }
          
            if(runflag == true) 
            {				        
				//	  GOTO( &ra_step, &dec_step);    //执行GOTO任务
	            runflag = false;	
	            AddStep = (ra_step*1.5)/250;  //时间*步进
	            ra_step = ra_step + AddStep;
				ControlMotor(ENABLE);
			  	ControlCover(ENABLE);
				SetSpeed(2000);
				SetSpeedCover(2000);
               // current_pos[0] = CURRENT_POS_RA ( target_ra, ra_step, RA_STP_ANGLE );   //更新当前指向
               // current_pos[1] = CURRENT_POS_DEC ( target_dec, dec_step, DEC_STP_ANGLE );
            }
     
        }
		 
	}	
}

/*********************************************END OF FILE**********************/

