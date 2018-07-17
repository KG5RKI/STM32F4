#include "stm32f4xx.h"                  // Device header
#include "my_gpio.h"
#include "my_led.h"

void LED_GPIO_Init() {
	
	/* Enable GPIOD clock */
	RCC->AHB1ENR |= (1<<3);
	
	/* Set GPIOD mode to output */
	GPIOD->MODER |= (GPIO_MODE_OUTPUT << 24);
	GPIOD->MODER |= (GPIO_MODE_OUTPUT << 26);
	GPIOD->MODER |= (GPIO_MODE_OUTPUT << 28);
	GPIOD->MODER |= (GPIO_MODE_OUTPUT << 30);
}

void LED_On(uint8_t ld) {
	GPIOD->BSRR |= (1 << ld);
}

void LED_Off(uint8_t ld) {
	GPIOD->BSRR |= (1 << (16+ld));
}

void LED_Toggle(uint8_t ld) {
	uint8_t led_status = ((GPIOD->ODR >> ld) & 0x1);
	
	if (led_status == 1) {
		for (int i = 0; i < 3; i++) {
			LED_Off(ld);
			for (int j = 0; j < 500000; j++);
			LED_On(ld);
			for (int j = 0; j < 500000; j++);
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			LED_On(ld);
			for (int j = 0; j < 500000; j++);
			LED_Off(ld);
			for (int j = 0; j < 500000; j++);
		}
	}
}

void LED_Init() {
	LED_GPIO_Init();
}
