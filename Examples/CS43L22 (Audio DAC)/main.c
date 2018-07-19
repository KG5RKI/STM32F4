#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"
#include "stm32f4xx_i2s_custom.h"
#include "stm32f4xx_led_custom.h"

#include "cs43l22.h"
#include "cs43l22_beep_generator.h"

int main(void)
{
	CS43L22_GPIO_Init();
	I2C1_Init();
	LED_Init();
	CS43L22_PowerUp();
	CS43L22_Configure_Interface();
	
	uint8_t chip_id = I2C1_Read(CS43L22_DEVICE_ADDR, CHIP_ID_REG);
	
	if ((chip_id>>3) == 0x1C) {
		LED_Toggle(12);
	}
	
	CS43L22_Config_BeepGenerator();
	
	return 0;
}
