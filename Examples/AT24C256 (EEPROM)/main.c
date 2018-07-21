#include "stm32f4xx.h"                  // Device header

#include "my_gpio.h"
#include "my_i2c.h"
#include "my_led.h"

int main() {
	
	/* Blue LED blinks - Data sent successfully
	 * Green LED blinks - Data received successfully
	 * Red LED on - Data not matched
	 * Green LED on - Sent and received data matches
	 */
	
	LED_Init();
	I2C1_Init();
	
	/* APPLICATION CODE STARTS HERE */

	LED_Toggle(14);
	EEPROM_256K_I2C1_Byte_Write(EEPROM_1_256K_ADDR, 0xCCC, 0xAA);
	uint8_t read_d = EEPROM_256K_I2C1_Random_Read(EEPROM_1_256K_ADDR, 0xCCC);
	
	LED_Toggle(12);
	
	if (read_d == 0xAA) {
		LED_On(12);
	}
	
	/* APPLICATION CODE ENDS HERE */
	
	while (1) {
	}
	
	return 0;
}
