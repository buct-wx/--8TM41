#include "./BSP/LED/led.h"


/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */
	LED2_GPIO_CLK_ENABLE();                                 /* LED2时钟使能 */
	LED3_GPIO_CLK_ENABLE();                                 /* LED3时钟使能 */
	LED4_GPIO_CLK_ENABLE();                                 /* LED4时钟使能 */
	LED5_GPIO_CLK_ENABLE();                                 /* LED5时钟使能 */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
	
	gpio_init_struct.Pin = LED2_GPIO_PIN;                   /* LED2引脚 */
    HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_init_struct);       /* 初始化LED2引脚 */
	
	gpio_init_struct.Pin = LED3_GPIO_PIN;                   /* LED3引脚 */
    HAL_GPIO_Init(LED3_GPIO_PORT, &gpio_init_struct);       /* 初始化LED3引脚 */
	
	gpio_init_struct.Pin = LED4_GPIO_PIN;                   /* LED3引脚 */
    HAL_GPIO_Init(LED4_GPIO_PORT, &gpio_init_struct);       /* 初始化LED3引脚 */
	
	gpio_init_struct.Pin = LED5_GPIO_PIN;                   /* LED3引脚 */
    HAL_GPIO_Init(LED5_GPIO_PORT, &gpio_init_struct);       /* 初始化LED3引脚 */
    
    LED0(1);                                                /* 关闭 LED0 */
    LED1(1);                                                /* 关闭 LED1 */
	LED2(1);                                                /* 关闭 LED2 */
	LED3(1);                                                /* 关闭 LED3 */
	LED4(1);                                                /* 关闭 LED4 */
	LED5(1);                                                /* 关闭 LED5 */
}
