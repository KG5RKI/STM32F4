#include "stm32f4xx.h"                  // Device header
#include "EventRecorder.h"              // Keil.ARM Compiler::Compiler:Event Recorder
#include "stdio.h"

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"
#include "stm32f4xx_i2s_custom.h"
#include "stm32f4xx_led_custom.h"

#include "cs43l22.h"

int main(void)
{
	/* Initialize the EventRecorder */
	EventRecorderInitialize(EventRecordAll, 1);
	
	/* Initialize all required peripherals */
	CS43L22_GPIO_Init();
	LED_Init();
	I2C1_Init();
	I2S3_Init();
	
	CS43L22_PowerUp();
	
	CS43L22_Config_BeepGenerator();
	
	while (1) {
		for (int data = 0x7777; data < 0xFFFF; data++) {
			I2S3_SendData(data);
			for (int d = 0; d < 1000; d++);
		}
	}
	
	return 0;
}
