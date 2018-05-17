#include "stm32f4xx.h"                  // Device header

void delay(void) {
	for (int i = 0; i<500000; i++){}
}

int main(void) {
	
	/* Program to blink LD3, connected to GPIOD, Pin 13 */
	
	/* 1. Enable clock, and set the AHB1ENR register to 0x00 */
	RCC -> AHB1ENR = 0x00;
	
	/* 2. Enable GPIOD, through AHB1ENR register */
	RCC -> AHB1ENR |= (1<<3);
	
	/* 3. Set GPIOD, Pin 13 mode to output(0x01) */
	GPIOD -> MODER |= 0x04000000;
	
	/* 4. Write data in the GPIOD, ODR(Output Data Register) */
	while(1) {
		GPIOD -> ODR = (1<<13);
		delay();
		GPIOD -> ODR = (0<<13);
		delay();
	}
	return 0;
}

