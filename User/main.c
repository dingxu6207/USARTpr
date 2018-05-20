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
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
u8 data_receive_buffer[USART_REC_LEN];  //来自于串口DMA输入
int main(void)
{	
  	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  	USART_Config();
	
		SysTick_Init();
	
		DMA_TX_init((u32)data_receive_buffer, USART_REC_LEN);
    DMA_RX_init((u32)data_receive_buffer, USART_REC_LEN);
	
 	 while(1)
	{	
		 if(data_receive_buffer[USART_REC_LEN - 1] == 1)  //DMA收到消息标志
        {
            data_receive_buffer[USART_REC_LEN - 1] = 0; //清理标志

            printf("it is ok!\n");
        }
		 
	}	
}
/*********************************************END OF FILE**********************/
