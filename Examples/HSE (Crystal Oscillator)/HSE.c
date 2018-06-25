#include "stm32f4xx.h"                  // Device header

void delay() {
	for (int i = 0; i < 1000000; i++) {
	}
}

int main() {
	
	/* HSE On */
	RCC -> CR |= (1<<16);
	
	/* Wait until HSE ready */
	while(RCC -> CR & (1<<17)) {
	}
	
	/* HSE oscillator selected as system clock */
	RCC -> CFGR &= ~(0x1<<1);
	RCC -> CFGR |= 0x01;
	
	RCC -> AHB1ENR |= (1<<3);
	GPIOD -> MODER |= 0x55000000;
	
	while(1) {
		GPIOD -> BSRR |= (1<<12);
		delay();
		GPIOD -> BSRR |= (1<<(12+16));
		delay();
	}
		
	return 0;
}

