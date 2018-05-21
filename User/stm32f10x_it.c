/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_TiMbase.h" 
#include "bsp_TimeCover.h"
#include "led.h"
#include "stdbool.h"
#include "command.h"

extern void TimingDelay_Decrement(void);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	 TimingDelay_Decrement();
}

// 串口中断服务函数
extern u8 data_receive_buffer[USART_REC_LEN] ;
void DEBUG_USART_IRQHandler(void)
{   
	if ( USART_GetITStatus(USART1,USART_IT_IDLE) != RESET )
		{
      		data_receive_buffer[USART_REC_LEN-1] = USART1->SR;
			data_receive_buffer[USART_REC_LEN-1] = USART1->DR; //USART_IT_IDLE clear
			data_receive_buffer[USART_REC_LEN-1] = 1;
			DMA_Cmd(DMA1_Channel5,DISABLE);
			DMA_SetCurrDataCounter(DMA1_Channel5,USART_REC_LEN);  //reset size
			DMA_Cmd(DMA1_Channel5,ENABLE);
		}
}


u8 uCountStep = 1;
bool ledflag = true;
extern int ra_step, dec_step;
extern s32 current_pos[2], target_pos[2];
extern s32 target_ra, target_dec;
void BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET )
	{
        uCountStep++;
		    
	 if(uCountStep > 8) //RA轴运动标志置位及按运动情况修改记步数据
    {
        uCountStep = 1;
        if ( (ra_step) > 0 )
        {
            (ra_step)--;
			GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
        }
        if ( (ra_step) < 0 )
        {
            (ra_step)++;
            GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
        }
    }
		
     if((ra_step) == 0 )	//到位了就切换到RA正常速度跟踪
    {		
		ControlMotor(DISABLE);
    }
		
		 current_pos[0] = CURRENT_POS_RA ( target_ra, ra_step, RA_STP_ANGLE );   //更新当前指向
		
		    TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update); 
	}
}

u8 uCountStep1 = 1;

void COVER_TIM_IRQHandler(void)
{
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET ) 
	{
		   uCountStep1++;
		   // u8 dec_overflows = 8
       if(uCountStep1 > 8) //DEC轴运动标志置位及按运动情况修改记步数据
   {
        uCountStep1 = 1;
        if ( (dec_step) > 0 )
        {
            (dec_step)--;
             GPIO_SetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
        }
        if ( (dec_step) < 0 )
        {
            (dec_step)++;
            GPIO_ResetBits(DrDIR_GPIO_PORT, DrDIR_GPIO_PIN);
        }

   }
				if (dec_step == 0)
				{
            ControlCover(DISABLE);
				}
				
				current_pos[1] = CURRENT_POS_DEC ( target_dec, dec_step, DEC_STP_ANGLE );
				
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
	}
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
