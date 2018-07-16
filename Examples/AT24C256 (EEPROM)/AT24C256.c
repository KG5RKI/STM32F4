#include "stm32f4xx.h"                  // Device header

#define GPIO_MODE_INPUT		0x0
#define GPIO_MODE_OUTPUT	0x1
#define GPIO_MODE_AF			0x2
#define GPIO_MODE_ANALOG	0x3

#define GPIO_OTYPE_PP 0x0
#define GPIO_OTYPE_OD 0x1

#define GPIO_SPEED_LOW				0x0
#define GPIO_SPEED_MEDIUM			0x1
#define GPIO_SPEED_HIGH				0x2
#define GPIO_SPEED_VERY_HIGH	0x3

#define GPIO_NO_PULL		0x0
#define GPIO_PULL_UP		0x1
#define GPIO_PULL_DOWN	0x2

void LED_GPIO_Init() {
	
	/* Enable GPIOD */
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

void I2C1_GPIO_Init() {
	/* PB6 - I2C1_SCL, PB7 - I2C1_SDA */
}

void I2C1_Init() {
	I2C1_GPIO_Init();
}

int main() {
	LED_Init();
	return 0;
}
