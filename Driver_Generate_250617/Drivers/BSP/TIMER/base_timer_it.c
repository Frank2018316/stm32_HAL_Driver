#include "base_timer_it.h"
#include "led.h"

TIM_HandleTypeDef tim_base_handle = {0};


void base_text_init(void)
{

    led_init();
    baseTimerItInit(BASE_TIMX_INT,5000,8400);
}

void base_text_while(void)
{
    LED0_TOGGLE();
    HAL_Delay(200);
}

/**
 * @brief       ͨ�ö�ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ42M, ���Զ�ʱ��ʱ�� = 84Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 * @param       tim_baseHandle: ��ʱ��
 * @param       arr: �Զ���װֵ
 * @param       psc: Ԥ��Ƶϵ��
 * @retval      ��
 */
void  baseTimerItInit(TIM_TypeDef* TIM,uint16_t arr, uint16_t psc)
{
    

    /* ͨ�ö�ʱ��x */
    tim_base_handle.Instance = TIM;
    /* Ԥ��Ƶϵ�� */
    tim_base_handle.Init.Prescaler =psc -1;
     /* ��������ģʽ */
    tim_base_handle.Init.CounterMode = TIM_COUNTERMODE_UP; 
    /* �Զ�װ��ֵ */
    tim_base_handle.Init.Period = arr-1;
    /* autoӰ�ӼĴ���*/
    tim_base_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    /* ��ʼ����ʱ�� */
    if (HAL_TIM_Base_Init(&tim_base_handle) != HAL_OK)
    {
    Error_Handler();
    }
    /*�������ö�ʱ����TIM����ģʽ��Master Mode�� */
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&tim_base_handle, &sMasterConfig) != HAL_OK)
    {
    Error_Handler();
    }
    /* USER CODE BEGIN TIM6_Init 2 */
    
    /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
    HAL_TIM_Base_Start_IT(&tim_base_handle);
    /* USER CODE END TIM6_Init 2 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==BASE_TIMX_INT)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* ʹ��TIMxʱ�� */
    BASE_TIMX_INT_CLK_ENABLE();

    /* �����ж����ȼ�����ռ���ȼ��������ȼ� */
    HAL_NVIC_SetPriority(BASE_TIMX_INT_IRQn, 0, 0);
    /* ����ITMx�ж� */
    HAL_NVIC_EnableIRQ(BASE_TIMX_INT_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
}
/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void BASE_TIMX_INT_IRQHandler(void)
{
    /*���������Զ����IT*/
    HAL_TIM_IRQHandler(&tim_base_handle);
    /*�����ֶ�������һ��*/
    __HAL_TIM_CLEAR_IT(&tim_base_handle, TIM_IT_UPDATE);  /* �����ʱ������жϱ�־λ */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==BASE_TIMX_INT)
  {
    LED1_TOGGLE();
    
  }

}
