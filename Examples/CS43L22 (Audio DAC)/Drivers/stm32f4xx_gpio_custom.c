#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"

void GPIO_ClockInit(GPIO_TypeDef *port)
{
	if (port == GPIOA) {
		RCC->AHB1ENR |= (1 << 0);
	}
	else if (port == GPIOB) {
		RCC->AHB1ENR |= (1 << 1);
	}
	else if (port == GPIOC) {
		RCC->AHB1ENR |= (1 << 2);
	}
	else if (port == GPIOD) {
		RCC->AHB1ENR |= (1 << 3);
	}
	else if (port == GPIOE) {
		RCC->AHB1ENR |= (1 << 4);
	}
}

void GPIO_Config(GPIO_TypeDef *port, uint8_t pin, uint8_t MODE, uint8_t OTYPE, uint8_t OSPEED, uint8_t PULL)
{
	port->MODER |= (MODE << (2*pin));
	port->OTYPER |= (OTYPE << pin);
	port->OSPEEDR |= (OSPEED << (2*pin));
	port->PUPDR |= (PULL << (2*pin));
}

void GPIO_Config_AF(GPIO_TypeDef *port, uint8_t pin, uint8_t AF)
{
	if (pin <= 7) {
		port->AFR[0] |= (AF << (4*pin));
	}
	else {
		port->AFR[1] |= (AF << (4*(pin - 8)));
	}
}

void GPIO_SetPin(GPIO_TypeDef *port, uint8_t pin)
{
	port->BSRR |= (1 << pin);
}

void GPIO_ResetPin(GPIO_TypeDef *port, uint8_t pin)
{
	port->BSRR |= (1 << (pin + 16));
}
