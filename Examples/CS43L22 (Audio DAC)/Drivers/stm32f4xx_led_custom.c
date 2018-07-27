#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_led_custom.h"
#include "stm32f4xx_gpio_custom.h"

void LED_GPIO_Init()
{
	GPIO_ClockInit(GPIOD);
	GPIO_Config(GPIOD, 12, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_NO_PULL);	
	GPIO_Config(GPIOD, 13, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_NO_PULL);
	GPIO_Config(GPIOD, 14, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_NO_PULL);
	GPIO_Config(GPIOD, 15, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_NO_PULL);
}

void LED_Init()
{
	LED_GPIO_Init();
}

void LED_On(int ld)
{
	GPIO_SetPin(GPIOD, ld);
}

void LED_Off(int ld)
{
	GPIO_ResetPin(GPIOD, ld);
}

void LED_Toggle(int ld)
{
	for (int i = 0; i < 3; i++) {
		LED_On(ld);
		for (int j = 0; j < 500000; j++) {};
		LED_Off(ld);
		for (int j = 0; j < 500000; j++) {};
	}
}
