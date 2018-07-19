#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio_custom.h"

void GPIO_SetPin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	gpio_td->BSRR |= (1<<gpio_pin);
}

void GPIO_ResetPin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	gpio_td->BSRR |= (1<<(16 + gpio_pin));
}

void GPIO_TogglePin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	/* If pin is HIGH, set to LOW */
	if ((gpio_td->ODR >> gpio_pin) & 0x1) {
		gpio_td->ODR &= ~(1<<gpio_pin);
	}
	
	/* else if pin if LOW, set to HIGH */
	else {
		gpio_td->ODR |= (1<<gpio_pin);
	}
}

void GPIO_Toggle2_With_Delay(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	GPIO_TogglePin(gpio_td, gpio_pin);
	
	for (int i = 0; i < 500000; i++) {
		/* Delay */
	}
	
	GPIO_TogglePin(gpio_td, gpio_pin);
}

