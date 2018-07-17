#include "stm32f4xx.h"                  // Device header
#include "my_i2c.h"
#include "my_gpio.h"
#include "my_led.h"

int main() {
	LED_Init();
	I2C1_Init();
	return 0;
}
