#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_led_custom.h"

void LED_GPIO_Init()
{
	RCC->AHB1ENR |= (1<<3);
	GPIOD->MODER |= (0x55<<24);
}

void LED_Init()
{
	LED_GPIO_Init();
}

void LED_On(int ld)
{
	GPIOD->BSRR |= (1<<ld);
}

void LED_Off(int ld)
{
	GPIOD->BSRR |= (1<<(ld+16));
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
