#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0时钟使能 */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1时钟使能 */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2时钟使能 */
    WKUP_GPIO_CLK_ENABLE();                                     /* WKUP时钟使能 */

    gpio_init_struct.Pin = KEY0_GPIO_PIN;                       /* KEY0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = WKUP_GPIO_PIN;                       /* WKUP引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);           /* WKUP引脚模式设置,下拉输入 */

}

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY0_PRES, 1, KEY0按下
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 *              WKUP_PRES, 4, WKUP按下
 */


#define LONG_PRESS_TIME 2000  // 定义长按时间，单位为毫秒（2秒）

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY0_PRES, 1, KEY0按下
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 *              WKUP_PRES, 4, WKUP按下
 *              LONG_PRESS_KEY2, 5, KEY2长按
 *              LONG_PRESS_WKUP, 6, WKUP长按
 */
 
 
int count_key2 = 0;
int count_keyw	= 0;
uint8_t keyval = 0;
uint8_t count_f1 = 2;
uint8_t count_f2 = 2;

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;        /* 按键松开标志 */
    static uint32_t key_press_time_KEY2 = 0; /* 记录 KEY2 按下的时间 */
    static uint32_t key_press_time_WKUP = 0; /* 记录 WKUP 按下的时间 */


	if(KEY2==0)
	{
		delay_ms(2);
		if(KEY2==0&&count_key2<100)
		{
			count_key2++;
			keyval = 0;

		}
		if(count_key2==100)
		{
			
			count_key2++;
			keyval = 1;
			count_f1++;
			if(count_f1>=3)
			{
					count_f1 = 0;
			}
		}
	}
	else
	{
		if(count_key2!=0&&count_key2<100)
		{
			count_f1 = 2;
		}
		count_key2=0;
	}

	
	
	
  if(WK_UP==1)
	{
		delay_ms(2);
		if(WK_UP==1&&count_keyw<100)
		{
			count_keyw++;
			keyval = 2;

		}
		if(count_keyw==100)
		{
			
			count_keyw++;
			keyval = 3;
			count_f2++;
			if(count_f2>=3)
			{
					count_f2 = 0;
			}
		}
	}
	else
	{
		if(count_keyw!=0&&count_keyw<100)
		{
			count_f2 = 2;
		}
		count_keyw=0;
	}
//	if(WK_UP==1)
//	{
//		delay_ms(2);
//		if(WK_UP==1)
//		{
//			count_keyw++;
//			keyval = 2;
//		}
//		if(count_keyw>=100)
//		{
//			keyval = 3;
//		}
//	}
//	else
//	{
//		count_keyw=0;
//	}

    return keyval;  /* 返回键值 */
}
