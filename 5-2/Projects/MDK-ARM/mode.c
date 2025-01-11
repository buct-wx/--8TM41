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
	LED4(0);
    LED5(0);
    delay_ms(1000);
    LED0_TOGGLE();
    delay_ms(1000);
	LED0_TOGGLE();
    LED1_TOGGLE();
	delay_ms(1000);
	LED1_TOGGLE();
	LED2_TOGGLE();
	delay_ms(1000);
	LED2_TOGGLE();
	LED3_TOGGLE();
	delay_ms(1000);
	LED3_TOGGLE();
	LED4_TOGGLE();
	delay_ms(1000);
	LED4_TOGGLE();
	LED5_TOGGLE();
	delay_ms(1000);
}

void mode_2(void)
{
	LED0(0); 					
    LED1(0);
    LED2(0);
    LED3(0);
	LED4(0);
    LED5(0);
    LED0_TOGGLE();
	LED3_TOGGLE();
    delay_ms(1000);
	LED0_TOGGLE();
	LED3_TOGGLE();
    LED1_TOGGLE();
	LED4_TOGGLE();
    delay_ms(1000);
	LED1_TOGGLE();
	LED4_TOGGLE();
    LED2_TOGGLE();
	LED5_TOGGLE();
    delay_ms(1000);
}
