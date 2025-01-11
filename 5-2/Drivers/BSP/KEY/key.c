#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       ������ʼ������
 * @param       ��
 * @retval      ��
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO���ò����洢���� */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0ʱ��ʹ�� */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1ʱ��ʹ�� */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2ʱ��ʹ�� */
    WKUP_GPIO_CLK_ENABLE();                                     /* WKUPʱ��ʹ�� */

    gpio_init_struct.Pin = KEY0_GPIO_PIN;                       /* KEY0���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);           /* KEY0����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2����ģʽ����,�������� */

    gpio_init_struct.Pin = WKUP_GPIO_PIN;                       /* WKUP���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);           /* WKUP����ģʽ����,�������� */

}

/**
 * @brief       ����ɨ�躯��
 * @note        �ú�������Ӧ���ȼ�(ͬʱ���¶������): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, ���庬������:
 *   @arg       0,  ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
 *                  �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
 *   @arg       1,  ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
 * @retval      ��ֵ, ��������:
 *              KEY0_PRES, 1, KEY0����
 *              KEY1_PRES, 2, KEY1����
 *              KEY2_PRES, 3, KEY2����
 *              WKUP_PRES, 4, WKUP����
 */


#define LONG_PRESS_TIME 2000  // ���峤��ʱ�䣬��λΪ���루2�룩

/**
 * @brief       ����ɨ�躯��
 * @note        �ú�������Ӧ���ȼ�(ͬʱ���¶������): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, ���庬������:
 *   @arg       0,  ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
 *                  �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
 *   @arg       1,  ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
 * @retval      ��ֵ, ��������:
 *              KEY0_PRES, 1, KEY0����
 *              KEY1_PRES, 2, KEY1����
 *              KEY2_PRES, 3, KEY2����
 *              WKUP_PRES, 4, WKUP����
 *              LONG_PRESS_KEY2, 5, KEY2����
 *              LONG_PRESS_WKUP, 6, WKUP����
 */
 
 
int count_key2 = 0;
int count_keyw	= 0;
uint8_t keyval = 0;
uint8_t count_f1 = 2;
uint8_t count_f2 = 2;

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;        /* �����ɿ���־ */
    static uint32_t key_press_time_KEY2 = 0; /* ��¼ KEY2 ���µ�ʱ�� */
    static uint32_t key_press_time_WKUP = 0; /* ��¼ WKUP ���µ�ʱ�� */


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

    return keyval;  /* ���ؼ�ֵ */
}
