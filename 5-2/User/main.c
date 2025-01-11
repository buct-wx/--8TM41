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
	LED4(0);
    LED5(0);
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
	else if(indexled==4)
    {
        LED4(1); 
    }
	else if(indexled==5)
    {
        LED5(1); 
    }
    indexled++;
    if(indexled>=6)
    {
        indexled = 0;
    }
}

void mode__2(void)
{
    close_all();
    if(indexled==0)
    {
        LED0(1);
		LED3(1);
    }
    else if(indexled==1)
    {
        LED1(1);
		LED4(1);		
    }
    else if(indexled==2)
    {
        LED2(1);
		LED5(1);
    }
    indexled++;
    if(indexled>=3)
    {
        indexled = 0;
    }
}

extern uint8_t count_f1;
extern uint8_t count_f2;
int main(void)
{

    uint8_t current_mode = 0;  // ��ǰģʽ��־��0Ϊmode_1��1Ϊmode_2
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    led_init();                             /* ��ʼ��LED */
    //beep_init();                            /* ��ʼ�������� */
    key_init();                             /* ��ʼ������ */
    LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);
	LED4(0);
	LED5(0);
	
	
	while(1)
    {
		current_mode = key_scan(0); 
		//����ģʽ1 Ĭ��Ƶ��1hz
        if (current_mode == 0) 
        {
            if(count % 100 == 0)
            {
                mode__1();
            }
        } 
		
		//����ģʽ1-Ƶ��1 0.4hz һ��2.5s
		else if(current_mode == 1  && count_f1 == 0)
		{
			if(count % 250 == 0)
            {
                mode__1();
            }
		}
		
		//����ģʽ1-Ƶ��2 1.9hz һ��0.53s
		else if(current_mode == 1  && count_f1 == 1)
		{
			if(count % 53 == 0)
            {
                mode__1();
            }			
		}
		
		//����ģʽ1-Ƶ��3 2.6hz һ��0.38s
		else if(current_mode == 1  && count_f1 == 2)
		{
			if(count % 38 == 0)
			{
                mode__1();
            }
		}
	
		
		
		//Ĭ��Ƶ��1hz
        else if(current_mode == 2)
        {
            if(count % 100 == 0)
            {
                mode__2();
            }
        }
		//����ģʽ2-Ƶ��1 0.3hz һ��3.3s
				else if(current_mode == 3  && count_f2 == 0)
        {
            if(count % 333 == 0)
            {
                mode__2();
            }
        }
		//����ģʽ2-Ƶ��2	1.6hz һ��0.625s
				else if(current_mode == 3  && count_f2 == 1)
        {
            if(count % 63 == 0)
            {
                mode__2();
            }
        }
		//����ģʽ2-Ƶ��3	2.3hz һ��0.43s	
				else if(current_mode == 3  && count_f2 == 2)
        {
            if(count % 43 == 0)
            {
                mode__2();
            }
        }
		count++;

        // ��ʱ������ģʽ�л�����
        delay_ms(10);
    }
}
