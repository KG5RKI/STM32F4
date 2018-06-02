#include "stm32f4xx.h"                  // Device header

/* Vss     - GND
 * Vcc     - Vcc
 * Vee     - GND/Potentiometer
 * PE4     - RS
 * GND     - RW 
 * PE5     - EN
 * PE7..14 - D0..D7
 * +5V/+3V - LED+
 * GND     - LED-
 */
 
void delay(int count) {
	for (int i = 0; i<count; i++) {
	}
}

void LCD_Data(int data) {
	
	/* Send data to PE7..14 */
	GPIOE -> ODR |= (data<<7);
	
	/* Set PE4(RS) to 1(Data Mode) */
	GPIOE -> BSRR = (1<<4);
	
	/* Trigger EN with falling edge, PE5 - 1 then 0 */
	GPIOE -> BSRR = (1<<5);
	delay(10);
	GPIOE -> BSRR = (1<<(16+5));
	delay(1000);
}

void LCD_Command(int cmd) {
	
	/* Send cmd to PE7..14 */
	GPIOE -> ODR |= (cmd<<7);
	
	/* Set PE4(RS) to 0(Command Mode) */
	GPIOE -> BSRR = (1<<(16+4));
	
	/* Trigger EN with falling edge, PE5 - 1 then 0 */
	GPIOE -> BSRR = (1<<5);
	delay(10);
	GPIOE -> BSRR = (1<<(16+5));
	delay(1000);
}

void LCD_Initialize() {
	LCD_Command(0x38);
	LCD_Command(0x0E);
	LCD_Command(0x01);
	LCD_Command(0x80);
}

int main() {
	
	/* Enable clock on GPIOE */
	RCC -> AHB1ENR |= (1<<4);
	
	/* Set PE4..5 & PE7..14 mode to output */
	GPIOE -> MODER = 0x15554500;
	
	LCD_Initialize();
	
	LCD_Data('H');
	LCD_Data('e');
	LCD_Data('l');
	LCD_Data('l');
	LCD_Data('o');
	
	/* Go to next line */
	LCD_Command(0xC0);
	
	LCD_Data('W');
	LCD_Data('o');
	LCD_Data('r');
	LCD_Data('l');
	LCD_Data('d');
	
	while(1) {
	}
	
	return 0;
}

