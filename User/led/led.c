#include "led.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h" 

void LEDINIT(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 
     /*����LED��ص�GPIO����ʱ��*/
	 RCC_APB2PeriphClockCmd( LED_GPIO_CLK | LED_GPIO_CLK, ENABLE);

     /*ѡ��Ҫ���Ƶ�GPIO����*/
	 GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	
	
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);			
}

extern u8 uCountStep ;
extern u8 uCountStep1;

void GOTO ( int *ra_step, int *dec_step)  //���������ƶ��������
{
     u8 ra_overflows = 8, dec_overflows = 8;

	ControlMotor(ENABLE);
	ControlCover(ENABLE);
    if((*ra_step) == 0 )	//��λ�˾��л���RA�����ٶȸ���
    {		
		ControlMotor(DISABLE);
    }

     if((*dec_step) == 0 )	//��λ��DECֹͣ
    {
		ControlCover(DISABLE);
    }

    if(uCountStep > ra_overflows) //RA���˶���־��λ�����˶�����޸ļǲ�����
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

   if(uCountStep1 > dec_overflows) //DEC���˶���־��λ�����˶�����޸ļǲ�����
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
