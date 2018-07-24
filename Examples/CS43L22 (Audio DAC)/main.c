#include "stm32f4xx.h"                  // Device header
#include "EventRecorder.h"              // Keil.ARM Compiler::Compiler:Event Recorder
#include "stdio.h"

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"
#include "stm32f4xx_i2s_custom.h"
#include "stm32f4xx_led_custom.h"

#include "cs43l22.h"
#include "cs43l22_beep_generator.h"

int main(void)
{
	/* Initialize the EventRecorder */
	EventRecorderInitialize(EventRecordAll, 1);
	
	/* Initialize all required peripherals */
	CS43L22_GPIO_Init();
	LED_Init();
	I2C1_Init();
	I2S3_Init();
	
	/* Power up the audio DAC */
	CS43L22_PowerUp();
	
	fprintf(stdout, "Chip ID         = 0x%x\n", I2C1_Read(CS43L22_DEVICE_ADDR, CHIP_ID_REG));
	fprintf(stdout, "Power Control 1 = 0x%x\n", I2C1_Read(CS43L22_DEVICE_ADDR, POWER_CONTROL_1));
	
	while (1) {
		I2S3_SendData(0xAA);
	}
	//CS43L22_Config_BeepGenerator();
	
	return 0;
}
