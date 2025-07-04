#ifndef  __GTP_TIMER_OC_PWM_TOGGLE_H_
#define  __GTP_TIMER_OC_PWM_TOGGLE_H_

#include "main.h"


#define GTP_TIMX_OC_PWM_DC_HALF_ENABLE                  0  /* 0: 禁止输出比较PWM占空比为50%, 1: 允许输出比较PWM占空比为50% */
#define GTP_TIMX_OC_PWM_IT_DC_HALF_ENABLE               1  /* 0: 禁止输出比较PWM占空比为50%中断, 1: 允许输出比较PWM占空比为50%中断 */

#define GTP_TIMX_INT                       TIM9
#define GTP_TIMX_INT_IRQn                  TIM1_BRK_TIM9_IRQn
#define GTP_TIMX_INT_IRQHandler            TIM1_BRK_TIM9_IRQHandler
#define __GTP_TIMX_INT_CLK_ENABLE()        do{ __HAL_RCC_TIM9_CLK_ENABLE(); }while(0)  /* TIM9 时钟 */


// 对于IC的定义
#define GTP_CH1_Pin                          GPIO_PIN_5
#define GPT_CH1_GPIO_Port                    GPIOE
#define GPT_CH1_GPIO_MODE                    GPIO_MODE_AF_PP
#define GPT_CH1_IC_GPIO_PULL                 GPIO_PULLDOWN
#define GPT_CH1_OC_GPIO_PULL                 GPIO_NOPULL
#define GPT_CH1_GPIO_AF                      GPIO_AF3_TIM9
#define __GPT_CH1_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0U)

#define ARR_MAX_VALUE                        0x5000 // ARR的最大值

void GTP_text(void);
static void GPIO_CH1_Init(uint8_t pinPull);
void __Set_GTP_OC_PwmToggle(uint16_t Period);
void GTP_OC_PwmToggle_TimerInit(TIM_TypeDef* TimInstance,uint16_t arr, uint16_t psc,uint8_t setARPE,uint8_t setOCMode);


#endif // __GTP_TIMER_OC_PWM_TOGGLE_H_
