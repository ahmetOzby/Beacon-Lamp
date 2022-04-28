/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_clk.h"

/* Private defines -----------------------------------------------------------*/

#define DELAY_TIME      3399
#define LED1_PORT       GPIOD
#define LED1_PIN        GPIO_PIN_4
#define LED2_PORT       GPIOD
#define LED2_PIN        GPIO_PIN_5
#define LED3_PORT       GPIOD
#define LED3_PIN        GPIO_PIN_6
#define LED4_PORT       GPIOD
#define LED4_PIN        GPIO_PIN_3
#define LED5_PORT       GPIOD
#define LED5_PIN        GPIO_PIN_2
#define LED6_PORT       GPIOC
#define LED6_PIN        GPIO_PIN_3
#define SIGNAL_PORT     EXTI_PORT_GPIOC
#define SIGNAL_PIN      GPIO_PIN_4

#define HIGH            1
#define LOW             0

/* Private function prototypes -----------------------------------------------*/
void AESK_BeaconLamp_Off(void);
void AESK_BeaconLamp_On(void);
void AESK_Delay(uint32_t ms);

extern uint8_t exti_flag;
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  
  CLK_DeInit();
  CLK_HSECmd(DISABLE);
  CLK_LSICmd(DISABLE);
  CLK_HSICmd(ENABLE);
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == 0);
  
  CLK_ClockSwitchCmd(ENABLE);
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV4);
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_IT);
  //GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);
  GPIO_Init(LED1_PORT, LED1_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED2_PORT, LED2_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED3_PORT, LED3_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED4_PORT, LED4_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED5_PORT, LED5_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED6_PORT, LED6_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  EXTI_DeInit();
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_RISE_ONLY);
    enableInterrupts();
  AESK_BeaconLamp_Off();
  /* Infinite loop */
  while (1)
  {
    if(exti_flag == 3)
    {
        AESK_BeaconLamp_On();
        exti_flag = 0;
    }
    else
    {
        AESK_BeaconLamp_Off();
    }
  }
  
}

void AESK_Delay(uint32_t ms)
{
  while(ms--);
}

 void AESK_BeaconLamp_Off(void)
 {
    GPIO_WriteLow(LED1_PORT, LED1_PIN);
    GPIO_WriteLow(LED2_PORT, LED2_PIN);
    
    GPIO_WriteLow(LED3_PORT, LED3_PIN);
    GPIO_WriteLow(LED4_PORT, LED4_PIN);
    GPIO_WriteLow(LED5_PORT, LED5_PIN);
    GPIO_WriteLow(LED6_PORT, LED6_PIN);
 }

void AESK_BeaconLamp_On(void)
{
  GPIO_WriteHigh(LED1_PORT, LED1_PIN);
  GPIO_WriteLow(LED6_PORT, LED6_PIN);
  AESK_Delay(DELAY_TIME);
  
  GPIO_WriteHigh(LED2_PORT, LED2_PIN);
  GPIO_WriteLow(LED1_PORT, LED1_PIN);
  AESK_Delay(DELAY_TIME);
  
  GPIO_WriteHigh(LED3_PORT, LED3_PIN);
  GPIO_WriteLow(LED2_PORT, LED2_PIN);
  AESK_Delay(DELAY_TIME);
  
  GPIO_WriteHigh(LED4_PORT, LED4_PIN);
  GPIO_WriteLow(LED3_PORT, LED3_PIN);
  AESK_Delay(DELAY_TIME);
  
  GPIO_WriteHigh(LED5_PORT, LED5_PIN);
  GPIO_WriteLow(LED4_PORT, LED4_PIN);
  AESK_Delay(DELAY_TIME);
  
  GPIO_WriteHigh(LED6_PORT, LED6_PIN);
  GPIO_WriteLow(LED5_PORT, LED5_PIN);
  AESK_Delay(DELAY_TIME);
}
  


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
