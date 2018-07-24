#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"
#include "stm32f4xx_i2s_custom.h"

#include "cs43l22.h"

void CS43L22_GPIO_Init()
{
	RCC->AHB1ENR |= (1<<3); //GPIOD clock enable
	
	/* Configure Reset pin - PD4 */
	GPIOD->MODER |= (1<<8); //Output
	GPIOD->OSPEEDR |= (1<<8); //Medium speed
	GPIOD->OTYPER &= ~(1<<4); //Push pull
	GPIOD->PUPDR |= (2<<8); //Pull down
}

void CS43L22_PowerUp()
{
	/* 1. Reset CS43L22 by toggling PD4 */
	GPIO_SetPin(GPIOD, 4);
			
	/* 2. Set POWER_CONTROL_1 register to 0x9E */
	I2C1_Write(CS43L22_DEVICE_ADDR, POWER_CONTROL_1, 0x9E);
	
	/* 3. Configure the auto-detect circuitry */
	I2C1_Write(CS43L22_DEVICE_ADDR, CLOCKING_CONTROL, 0x80);
}

void CS43L22_PowerDown()
{
	/* 1. Mute the DACs */
	
	/* 2. Set POWER_CONTROL_1 register to 0x02 */
	I2C1_Write(CS43L22_DEVICE_ADDR, POWER_CONTROL_1, 0x02);
	
	/* 3. Set ~RESET to LOW */
	GPIO_ResetPin(GPIOD, 4);
}

void CS43L22_Headphone_Mute()
{
	uint8_t playback_ctrl2 = 0;
	playback_ctrl2 |= (3<<6);
	I2C1_Write(CS43L22_DEVICE_ADDR, PLAYBACK_CONTROL_2, playback_ctrl2);
}

void CS43L22_Headphone_Unmute()
{
	uint8_t playback_ctrl2 = 0;
	playback_ctrl2 &= ~(3<<6);
	I2C1_Write(CS43L22_DEVICE_ADDR, PLAYBACK_CONTROL_2, playback_ctrl2);
}

void CS43L22_Speaker_Mute()
{
	uint8_t playback_ctrl2 = 0;
	playback_ctrl2 |= (3<<4);
	I2C1_Write(CS43L22_DEVICE_ADDR, PLAYBACK_CONTROL_2, playback_ctrl2);
}

void CS43L22_Speaker_Unmute()
{
	uint8_t playback_ctrl2 = 0;
	playback_ctrl2 &= ~(3<<4);
	I2C1_Write(CS43L22_DEVICE_ADDR, PLAYBACK_CONTROL_2, playback_ctrl2);
}
