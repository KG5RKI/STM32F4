#include "stm32f4xx.h"                  // Device header
#include "my_i2c.h"
#include "my_gpio.h"
#include "my_led.h"

#define EEPROM_256K_ADDR 0x50

/* Data to be stored at 0x0FFF in EEPROM */
#define FIRST_WORD_ADDR 0x0F
#define SECOND_WORD_ADDR 0xFF

int main() {
	
	/* Blue LED blinks - Data sent successfully
	 * Green LED blinks - Data received successfully
	 * Red LED on - Data not matched
	 * Green LED on - Sent and received data matches
	 */
	
	LED_Init();
	I2C1_Init();
	
	/* ------------------------------ */
	uint8_t write_data = 0xCC;
	uint8_t read_data;
	I2C1_Write_1ByteData(EEPROM_256K_ADDR, FIRST_WORD_ADDR, SECOND_WORD_ADDR, write_data);
	LED_Toggle(15);
	read_data = I2C1_Read_1ByteData(EEPROM_256K_ADDR, FIRST_WORD_ADDR, SECOND_WORD_ADDR);
	LED_Toggle(12);
	
	if (read_data == write_data) {
		LED_On(12);
	}
	else {
		LED_On(14);
	}
	/* ------------------------------ */
	
	while (1) {
	}
	
	return 0;
}
