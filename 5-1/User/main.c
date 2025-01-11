#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MODE/mode.h"

int indexled = 0;
int count = 0;

void close_all(void)
{
    LED0(0); 
    LED1(0);
    LED2(0);
    LED3(0);
}

void mode__1(void)
{
    close_all();
    if(indexled==0)
    {
        LED0(1); 
    }
    else if(indexled==1)
    {
        LED1(1); 
    }
    else if(indexled==2)
    {
        LED2(1); 
    }
    else if(indexled==3)
    {
        LED3(1); 
    }
    indexled++;
    if(indexled>=4)
    {
        indexled = 0;
    }
}

void mode__2(void)
{
    close_all();
    if(indexled ==0)
    {
        LED3(1);    
    }
    if(indexled ==1)        
    {
        LED3(0);    
    }        
    indexled++;
    if(indexled>=2)
    {
        indexled = 0;
    }
}
    

int main(void)
{
    uint8_t key;
    uint8_t current_mode = 0;  // ��ǰģʽ��־��0Ϊmode_1��1Ϊmode_2
    uint8_t last_key = 0;      // ��һ�ΰ���״̬
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    led_init();                             /* ��ʼ��LED */
    key_init();                             /* ��ʼ������ */

    LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);

    while(1)
    {
        key = key_scan(0);                  /* �õ���ֵ */
        // ֻ�ڰ��������仯ʱ����ģʽ�л�
        if (key != last_key)  
        {
            // ��������ʱ�Ž���ģʽ�л�
            if (key)  
            {
                switch (key)
                {
                    case WKUP_PRES:  
                        // �л���mode_1
                        current_mode = 0;
                        break;

                    case KEY2_PRES:  
                        // �л���mode_2
                        current_mode = 1;
                        break;

                    default: 
                        break;
                }
                // �������º������ʱ���ⶶ��
                delay_ms(10);  // �����ʵ���ȥ������ʱ
            }
        }

        last_key = key;  // ���浱ǰ����״̬�����´��ж�ʹ��

        if (current_mode == 0) 
        {
            if(count % 5 == 0)
            {
                mode__1();
            }
        } 
        else 
        {
            if(count % 5 == 0)
            {
                mode__2();
            }
        }
		count++;

        // ��ʱ������ģʽ�л�����
        delay_ms(100);
    }
}
