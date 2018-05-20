/**
  ******************************************************************************
  * @file    main.c
  * @author  dingxu
  * @version V1.0
  * @date    2018-05-20
  * @brief   �����
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "dma.h"
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
u8 data_receive_buffer[USART_REC_LEN];  //�����ڴ���DMA����
int main(void)
{	
  	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  	USART_Config();
	
		SysTick_Init();
	
		DMA_TX_init((u32)data_receive_buffer, USART_REC_LEN);
    DMA_RX_init((u32)data_receive_buffer, USART_REC_LEN);
	
 	 while(1)
	{	
		 if(data_receive_buffer[USART_REC_LEN - 1] == 1)  //DMA�յ���Ϣ��־
        {
            data_receive_buffer[USART_REC_LEN - 1] = 0; //�����־

            printf("it is ok!\n");
        }
		 
	}	
}
/*********************************************END OF FILE**********************/
