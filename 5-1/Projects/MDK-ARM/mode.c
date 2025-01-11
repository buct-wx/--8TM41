#include "./BSP/MODE/mode.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/KEY/key.h"


void mode_1(void)
{
	LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);
    delay_ms(1000);
    LED0_TOGGLE();
    delay_ms(1000);
    LED1_TOGGLE();
	delay_ms(1000);
	LED2_TOGGLE();
	delay_ms(1000);
	LED3_TOGGLE();
	delay_ms(1000);
}

void mode_2(void)
{
    LED3_TOGGLE();
    delay_ms(1000);
    LED3_TOGGLE();
    delay_ms(1000);
}
