#include "./BSP/LED/led.h"


/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1ʱ��ʹ�� */
	LED2_GPIO_CLK_ENABLE();                                 /* LED2ʱ��ʹ�� */
	LED3_GPIO_CLK_ENABLE();                                 /* LED3ʱ��ʹ�� */
	LED4_GPIO_CLK_ENABLE();                                 /* LED4ʱ��ʹ�� */
	LED5_GPIO_CLK_ENABLE();                                 /* LED5ʱ��ʹ�� */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1���� */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
	
	gpio_init_struct.Pin = LED2_GPIO_PIN;                   /* LED2���� */
    HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED2���� */
	
	gpio_init_struct.Pin = LED3_GPIO_PIN;                   /* LED3���� */
    HAL_GPIO_Init(LED3_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED3���� */
	
	gpio_init_struct.Pin = LED4_GPIO_PIN;                   /* LED3���� */
    HAL_GPIO_Init(LED4_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED3���� */
	
	gpio_init_struct.Pin = LED5_GPIO_PIN;                   /* LED3���� */
    HAL_GPIO_Init(LED5_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED3���� */
    
    LED0(1);                                                /* �ر� LED0 */
    LED1(1);                                                /* �ر� LED1 */
	LED2(1);                                                /* �ر� LED2 */
	LED3(1);                                                /* �ر� LED3 */
	LED4(1);                                                /* �ر� LED4 */
	LED5(1);                                                /* �ر� LED5 */
}
