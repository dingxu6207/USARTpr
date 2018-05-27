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
#include "stdbool.h"
#include "Exti44E.h"
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
u8 data_receive_buffer[USART_REC_LEN];  //�����ڴ���DMA����
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
  	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  	USART_Config();
	
	SysTick_Init();
	
	DMA_TX_init((u32)data_receive_buffer, USART_REC_LEN);
    DMA_RX_init((u32)data_receive_buffer, USART_REC_LEN);

    BASIC_TIM_Init();
    Cover_TIM_Init();

    EXTI_44E_Config();
   
	
 	while(1)
	{	
		 if(data_receive_buffer[USART_REC_LEN - 1] == 1)  //DMA�յ���Ϣ��־
        {
            data_receive_buffer[USART_REC_LEN - 1] = 0; //�����־

            decode_state = LX200( data_receive_buffer, current_pos, target_pos ); //LX200Э�����

            if(GOTO_CHECK(decode_state) == 0xff) //Ŀ��λ���뱸
            {
				if(current_pos[0] == 0 && current_pos[1] == 0) //�����ϵͳ�տ�ʼ���У��򽫵�һ�ε�GOTO��Ϣ����Ϊ��ǰλ��
                {
                    current_pos[0] = target_pos[0];
                    current_pos[1] = target_pos[1];
                    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
                }
                else  //����GOTOʱ������Ŀ��λ�ü��㲽�������򣬸��ݲ����ͷ������ϵ���õ�ʵ����Ҫ�Ĳ����ͷ���
                {
                    target_ra = target_pos[0];
                    target_dec = target_pos[1];
                    ra_step	= RA_STEP_CALCULATE(current_pos[0], target_pos[0], RA_STP_ANGLE );   //����������貽���ͷ��������Ŵ�����
                    dec_step = DEC_STEP_CALCULATE(current_pos[1], target_pos[1], DEC_STP_ANGLE );
                    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
									runflag = true;
									      
                }
            }
          
            if(runflag == true) 
            {				        
				//	  GOTO( &ra_step, &dec_step);    //ִ��GOTO����
	            runflag = false;	
	            AddStep = (ra_step*1.5)/250;  //ʱ��*����
	            ra_step = ra_step + AddStep;
				ControlMotor(ENABLE);
			  	ControlCover(ENABLE);
				SetSpeed(2000);
				SetSpeedCover(2000);
               // current_pos[0] = CURRENT_POS_RA ( target_ra, ra_step, RA_STP_ANGLE );   //���µ�ǰָ��
               // current_pos[1] = CURRENT_POS_DEC ( target_dec, dec_step, DEC_STP_ANGLE );
            }
     
        }
		 
	}	
}

/*********************************************END OF FILE**********************/

