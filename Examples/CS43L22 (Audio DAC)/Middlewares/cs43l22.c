#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"
#include "stm32f4xx_i2s_custom.h"

#include "cs43l22.h"

/******************** CS43L22 PERIPHERAL INITIALIZATION ********************/

void CS43L22_GPIO_Init()
{
	RCC->AHB1ENR |= (1<<3); //GPIOD clock enable
	
	/* Configure Reset pin - PD4 */
	GPIOD->MODER |= (1<<8); //Output
	GPIOD->OSPEEDR |= (1<<8); //Medium speed
	GPIOD->OTYPER &= ~(1<<4); //Push pull
	GPIOD->PUPDR |= (2<<8); //Pull down
}

/******************** POWER-UP & POWER-DOWN FUNCTIONS ********************/

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

/******************** DSP ENGINE SETTINGS ********************/
void CS43L22_Config_DSPEngine()
{
}

/******************** BEEP GENERATOR SETTINGS ********************/

void CS43L22_Config_BeepGenerator()
{
	/* Set master volume to +12dB */
	CS43L22_Set_MSTA(12);
	CS43L22_Set_MSTB(12);
	
	/* Set beep frequency to 2000Hz and on time to 1.20s */
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_FREQUENCY_AND_ON_TIME, 0xE3);
	
	/* Set off time to 1.23s and beep volume to +12dB */
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_VOLUME_AND_OFF_TIME, 0x06);
	
	/* Enable the beep geenrator */
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_AND_TONE_CONFIG, 0xA0);
}

/******************** VOLUME SETTINGS ********************/

void CS43L22_Set_MSTA(uint8_t dB)
{
	switch (dB) {
		case 12: I2C1_Write(CS43L22_DEVICE_ADDR, MASTER_VOLUME_CONTROL_A, 0x1E); break;
	}
}

void CS43L22_Set_MSTB(uint8_t dB)
{
	switch (dB) {
		case 12: I2C1_Write(CS43L22_DEVICE_ADDR, MASTER_VOLUME_CONTROL_B, 0x1E); break;
	}
}

void CS43L22_Headphone_Mute()
{
}

void CS43L22_Headphone_Unmute()
{
}

void CS43L22_Speaker_Mute()
{
}

void CS43L22_Speaker_Unmute()
{
}
