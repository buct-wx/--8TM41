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
    uint8_t current_mode = 0;  // 当前模式标志，0为mode_1，1为mode_2
    uint8_t last_key = 0;      // 上一次按键状态
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    led_init();                             /* 初始化LED */
    key_init();                             /* 初始化按键 */

    LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);

    while(1)
    {
        key = key_scan(0);                  /* 得到键值 */
        // 只在按键发生变化时处理模式切换
        if (key != last_key)  
        {
            // 按键按下时才进行模式切换
            if (key)  
            {
                switch (key)
                {
                    case WKUP_PRES:  
                        // 切换到mode_1
                        current_mode = 0;
                        break;

                    case KEY2_PRES:  
                        // 切换到mode_2
                        current_mode = 1;
                        break;

                    default: 
                        break;
                }
                // 按键按下后，添加延时避免抖动
                delay_ms(10);  // 设置适当的去抖动延时
            }
        }

        last_key = key;  // 保存当前按键状态，供下次判断使用

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

        // 延时，避免模式切换过快
        delay_ms(100);
    }
}
