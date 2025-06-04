#include "GTP_ic_input.h"
#include "debug_com.h"
#include "led.h"
Tim_State g_timxchy_cap_sta ={0};
uint16_t g_timxchy_cap_val = 0; /* ���벶��ֵ */  

/* USER CODE END 0 */

TIM_HandleTypeDef GPT_IC_Handle;


uint32_t timESum = 0;
uint8_t t = 0;

void GTP_IC_text_init(void)
{

    UART_Init(115200);
    led_init();
    gpio_init();
    GTP_TimerICInit(GTP_TIMX_IC_INT,0x10000-1,84-1);
    printf("hello world!! \r\n");
}


void GTP_IC_text_while(void)
{

    while (1)
    {
         /*����ɹ�*/
        if(1 == g_timxchy_cap_sta.finish)
        {
          /*�������*/
          timESum = g_timxchy_cap_sta.data;
          /*���ʱ���ܺ�*/
          timESum *= 65536;
          /*�ߵ�ƽ������ʱ��*/
          timESum += g_timxchy_cap_val;
          /* ��ӡ�ܵĸߵ�ƽʱ�� */
          printf("�ߵ�ƽ�������       HIGH.data:%d \r\n", g_timxchy_cap_sta.data); 
          printf("δ���������ʱ��   HIGH.value:%d us\r\n", g_timxchy_cap_val);
          printf("�ܸߵ�ƽ������ʱ�� %d = value * 65536 + data \r\n", timESum); 
          /*׼����һ�β���*/ 
          g_timxchy_cap_sta.finish  = 0;
          g_timxchy_cap_sta.state  = 0;
          g_timxchy_cap_sta.data  = 0;

        }

          LED0_TOGGLE();
          HAL_Delay(100);
    }
}




void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
      
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
	/*����Ϊ�����ԭ��---���ø�TIM5��Ϊ���벶��*/
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    /*����һ��Ҫ������PA0��Ϊ���뻹��Ҫ������Ҫ��Ȼ�ò���*/
	/*GPIO_InitStruct.Pull ������ �����볡������Ч�������벶��*/
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}



/* TIM5 init function */
void  GTP_TimerICInit(TIM_TypeDef* TIM,uint16_t arr, uint16_t psc)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  GPT_IC_Handle.Instance = TIM;
  GPT_IC_Handle.Init.Prescaler = psc;
  GPT_IC_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  GPT_IC_Handle.Init.Period = arr;
  GPT_IC_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&GPT_IC_Handle) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&GPT_IC_Handle, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&GPT_IC_Handle) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&GPT_IC_Handle, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&GPT_IC_Handle, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */
  /* ���������ж� + ���벶���жϡ�ͬʱ���������� */
  __HAL_TIM_ENABLE_IT(&GPT_IC_Handle, TIM_IT_UPDATE); 
  HAL_TIM_IC_Start_IT(&GPT_IC_Handle, TIM_CHANNEL_1);
  /* USER CODE END TIM5_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{


  if(tim_baseHandle->Instance==GTP_TIMX_IC_INT)
  {
  /* USER CODE BEGIN TIM5_MspInit 0 */

  /* USER CODE END TIM5_MspInit 0 */
    /* TIM5 clock enable */
    GTP_TIMX_IC_INT_CLK_ENABLE();

    /* TIM5 interrupt Init */
    HAL_NVIC_SetPriority(GTP_TIMX_IC_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GTP_TIMX_IC_INT_IRQn);
  /* USER CODE BEGIN TIM5_MspInit 1 */

  /* USER CODE END TIM5_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==GTP_TIMX_IC_INT)
  {
  /* USER CODE BEGIN TIM5_MspDeInit 0 */

  /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    GTP_TIMX_IC_INT_CLK_ENABLE();

    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    /* TIM5 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
  /* USER CODE BEGIN TIM5_MspDeInit 1 */

  /* USER CODE END TIM5_MspDeInit 1 */
  }
}

/**
  * @brief This function handles TIM5 global interrupt.
  */
void GTP_TIMX_IC_INT_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&GPT_IC_Handle);
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/*���벶���ж�*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /*finish = 0����û�в���ɹ�*/
  if (0 == g_timxchy_cap_sta.finish)
  {
    /*state = 1:��ʾ�Ѿ������������-->��δ���Ϊ�½��ش����ж�----�������岶��ֵ*/
      if(1 == g_timxchy_cap_sta.state)
      {
        /*��ǲ���ɹ�*/
          g_timxchy_cap_sta.finish = 1;
        /*��ȡ����ֵ */
          g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&GPT_IC_Handle, TIM_CHANNEL_1);
        /*��λ���벶���� */
        TIM_RESET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1);
        /*��������Ϊ������--׼����һ�β���*/
        TIM_SET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
      }
    /*state = 0:��ʾû�в����������-->����ǵ�һ�������ش����ж�--->�ȴ���һ�β���������*/
      else            
      {
        
        /*�����������ֵ*/
        g_timxchy_cap_sta.data = 0;
        /*���ò���ֵ��׼����ʼ��*/
        g_timxchy_cap_val = 0;
        /*��¼��һ��������*/
        g_timxchy_cap_sta.state = 1;

        /*�������ò���***********************************/
        /*�رն�ʱ��5*/
        __HAL_TIM_DISABLE(&GPT_IC_Handle);
        /*��ʱ��5 ��ʼ�� ������ֵ = 0*/
        __HAL_TIM_SET_COUNTER(&GPT_IC_Handle,0);
        /*��λ���벶���� */
        TIM_RESET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1);
        /*��������Ϊ������--�ȴ��½��ش�������if*/
        TIM_SET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
         /*��ʼ��ʱ��5----��ʼ����*/
        __HAL_TIM_ENABLE(&GPT_IC_Handle);
        /*�������ò���***********************************/    
      }
  }

    
}

/*��������ж�*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /*��ʱ������������---����ֻ����TIM5����ж�*/
  if(GTP_TIMX_IC_INT == htim->Instance)
  {
    /*��ʱ���Ѿ������ ��û����ɹ�*/
    if(0 == g_timxchy_cap_sta.finish)
    {
      /*�Ѿ�������������*/
      if(1 == g_timxchy_cap_sta.state)
      {
        /*����������---һֱ�Ǹߵ�ƽ�������������������*/
        if(0x3F == g_timxchy_cap_sta.data)
        {
          /*��λ���벶�񡾴�ʱ�ǵȴ��½��ز��񡿼��� */
          TIM_RESET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1);
          
         /*��ǿ�Ʊ�ǲ�����ɣ������ö�ʱ��ͨ�������ز���*/
          g_timxchy_cap_sta.finish = 1;
          /*��ȡ������ʱ =  Ϊ���ֵ*/
          g_timxchy_cap_val = 0XFFFF;
          
          /*�������벶�񡾴�ʱ�ǵȴ������ز��񡿼��ԣ����¿�ʼ���� */
          TIM_SET_CAPTUREPOLARITY(&GPT_IC_Handle, TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
        }
        /*��¼�������*/
        else
        {
          g_timxchy_cap_sta.data++;
        }
      }
    }
  }
}
/* USER CODE END 1 */
