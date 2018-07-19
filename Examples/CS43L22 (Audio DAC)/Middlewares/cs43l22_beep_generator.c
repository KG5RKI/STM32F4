#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_i2c_custom.h"

#include "cs43l22.h"
#include "cs43l22_beep_generator.h"

void CS43L22_Config_BeepGenerator()
{
	/* 1. Master volume control - set to +12dB */
	uint8_t master_vol = 0x18;
	I2C1_Write(CS43L22_DEVICE_ADDR, MASTER_VOLUME_CONTROL_A, master_vol);
	I2C1_Write(CS43L22_DEVICE_ADDR, MASTER_VOLUME_CONTROL_B, master_vol);
	
	/* 2. PCMx volume control to +12dB */
	uint8_t pcm_vol =  0x18;
	I2C1_Write(CS43L22_DEVICE_ADDR, PCMA_VOLUME, pcm_vol);
	I2C1_Write(CS43L22_DEVICE_ADDR, PCMB_VOLUME, pcm_vol);
	
	/* 3. Configure beep frequency to 521.74Hz & on time to 2.80s */
	uint8_t freq_on_time = 0x18;
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_FREQUENCY_AND_ON_TIME, freq_on_time);
	
	/* 4. Configure beep volume to 12dB & off time to 2.58s */
	uint8_t vol_off_time = 0x6;
	vol_off_time &= ~(7<<5);
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_VOLUME_AND_OFF_TIME, vol_off_time);
	
	/* 5. Configure beep mix & enable beep in multiple mode */
	uint8_t beep_tone = 0;
	beep_tone |= (2<<6);
	I2C1_Write(CS43L22_DEVICE_ADDR, BEEP_AND_TONE_CONFIG, beep_tone);
}
