#include "stm32f4xx.h"                  // Device header

void delay(){
	for (int i = 0; i<500000; i++){
	}
}

int main(void) {
	
	/* 1. Enable the clock to GPIOE */
	RCC -> AHB1ENR |= (1<<4);
	
	/* 2. Set PE1 as output(0x00) */
	GPIOE -> MODER = 0x01;
	
	while(1) {
		
		/* 3. Set PE1 bit */
		GPIOE -> BSRR = (1<<0);
		delay();
		
		/* Reset PE1 bit */
		GPIOE -> BSRR = (1<<(16+0));
		delay();
	}
	
	return 0;
}

