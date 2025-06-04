#include "key_exit.h"
#include "led.h"


void keYExit_text_init(void)
{
    led_init();                             /* ��ʼ��LED */
    key_exit_init();                           /* ��ʼ���ⲿ�ж����� */
    LED0(0);                                /* �ȵ������ */
}

void keYExit_text_while(void)
{
    HAL_Delay(1000);
}



void key_exit_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    /*Configure GPIO pins : KEY2_Pin KEY1_Pin KEY0_Pin */
    GPIO_InitStruct.Pin = KEY2_Pin|KEY1_Pin|KEY0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
        
        
    /*Configure GPIO pin : WKUP_Pin */
    GPIO_InitStruct.Pin = WKUP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 3);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/**
 * @brief       KEY0 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_Pin);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY1 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI3_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);         /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_Pin);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY2 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI2_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);        /* �����жϴ����ú��� ���KEY2�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_Pin);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       WK_UP �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void EXTI0_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_Pin);        /* �����жϴ����ú��� ���KEY_UP�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_Pin);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       �жϷ����������Ҫ��������
 *              ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for(uint16_t t = 0;t<2000;t++){;}
    switch(GPIO_Pin)
    {
        case KEY0_Pin:
            if (KEY0 == 0)
            {
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;

        case KEY1_Pin:
            if (KEY1 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */ 
            }
            break;

        case KEY2_Pin:
            if (KEY2 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;

        case WKUP_Pin:
            if (WK_UP == 1)
            {
                LED0(0);
                LED1(0);
            }
            break;

        default : break;
    }
}
