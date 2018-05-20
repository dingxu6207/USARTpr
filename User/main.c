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
#include "led.h"
#include "command.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h" 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
u8 data_receive_buffer[USART_REC_LEN];  //�����ڴ���DMA����
int main(void)
{	
	s32 current_pos[2]= {0,0}, target_pos[2]= {0,0};
	u8 decode_state=0;
	 s32 target_ra=0, target_dec=0;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    LEDINIT();
  	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  	USART_Config();
	
	SysTick_Init();
	
	DMA_TX_init((u32)data_receive_buffer, USART_REC_LEN);
    DMA_RX_init((u32)data_receive_buffer, USART_REC_LEN);

    BASIC_TIM_Init();
    Cover_TIM_Init();
	
 	while(1)
	{	
		 if(data_receive_buffer[USART_REC_LEN - 1] == 1)  //DMA�յ���Ϣ��־
        {
            data_receive_buffer[USART_REC_LEN - 1] = 0; //������־

            decode_state = LX200( data_receive_buffer, current_pos, target_pos ); //LX200Э�����

            if(GOTO_CHECK(decode_state) == 0xff) //Ŀ��λ���뱸
            {
				if(current_pos[0] == 0 && current_pos[1] == 0) //�����ϵͳ�տ�ʼ���У��򽫵�һ�ε�GOTO��Ϣ����Ϊ��ǰλ��
                {
                    current_pos[0] = target_pos[0];
                    current_pos[1] = target_pos[1];
                    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
                    SetSpeed(1000);
					SetSpeedCover(100);
					ControlMotor(ENABLE);
			  		ControlCover(ENABLE);
                }
                else  //����GOTOʱ������Ŀ��λ�ü��㲽�������򣬸��ݲ����ͷ������ϵ���õ�ʵ����Ҫ�Ĳ����ͷ���
                {
                    target_ra = target_pos[0];
                    target_dec = target_pos[1];
                    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
                }
            }
        }
		 
	}	
}
/*********************************************END OF FILE**********************/