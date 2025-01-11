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

    uint8_t current_mode = 0;  // 当前模式标志，0为mode_1，1为mode_2
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    led_init();                             /* 初始化LED */
    //beep_init();                            /* 初始化蜂鸣器 */
    key_init();                             /* 初始化按键 */
    LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);
	LED4(0);
	LED5(0);
	
	
	while(1)
    {
		current_mode = key_scan(0); 
		//进入模式1 默认频率1hz
        if (current_mode == 0) 
        {
            if(count % 100 == 0)
            {
                mode__1();
            }
        } 
		
		//进入模式1-频率1 0.4hz 一次2.5s
		else if(current_mode == 1  && count_f1 == 0)
		{
			if(count % 250 == 0)
            {
                mode__1();
            }
		}
		
		//进入模式1-频率2 1.9hz 一次0.53s
		else if(current_mode == 1  && count_f1 == 1)
		{
			if(count % 53 == 0)
            {
                mode__1();
            }			
		}
		
		//进入模式1-频率3 2.6hz 一次0.38s
		else if(current_mode == 1  && count_f1 == 2)
		{
			if(count % 38 == 0)
			{
                mode__1();
            }
		}
	
		
		
		//默认频率1hz
        else if(current_mode == 2)
        {
            if(count % 100 == 0)
            {
                mode__2();
            }
        }
		//进入模式2-频率1 0.3hz 一次3.3s
				else if(current_mode == 3  && count_f2 == 0)
        {
            if(count % 333 == 0)
            {
                mode__2();
            }
        }
		//进入模式2-频率2	1.6hz 一次0.625s
				else if(current_mode == 3  && count_f2 == 1)
        {
            if(count % 63 == 0)
            {
                mode__2();
            }
        }
		//进入模式2-频率3	2.3hz 一次0.43s	
				else if(current_mode == 3  && count_f2 == 2)
        {
            if(count % 43 == 0)
            {
                mode__2();
            }
        }
		count++;

        // 延时，避免模式切换过快
        delay_ms(10);
    }
}
