#include "stm32f4xx.h"                  // Device header

#define CS43L22_DEVICE_ADDR (uint8_t)0x4A

#define CHIP_ID_REG                 (uint8_t)0x01
#define POWER_CONTROL_1             (uint8_t)0x02
#define POWER_CONTROL_2             (uint8_t)0x04
#define CLOCKING_CONTROL            (uint8_t)0x05
#define INTERFACE_CONTROL_1         (uint8_t)0x06
#define INTERFACE_CONTROL_2         (uint8_t)0x07
#define PASS_A                      (uint8_t)0x08
#define PASS_B                      (uint8_t)0x09
#define ANALOG_ZC_SR                (uint8_t)0x0A
#define PASSTHROUGH_GANG_CONTROL    (uint8_t)0x0C
#define PLAYBACK_CONTROL_1          (uint8_t)0x0D
#define MISC_CONTROLS               (uint8_t)0x0E
#define PLAYBACK_CONTROL_2          (uint8_t)0x0F
#define PASS_A_VOLUME               (uint8_t)0x14
#define PASS_B_VOLUME               (uint8_t)0x15
#define PCMA_VOLUME                 (uint8_t)0x1A
#define PCMB_VOLUME                 (uint8_t)0x1B
#define BEEP_FREQUENCY_AND_ON_TIME  (uint8_t)0x1C
#define BEEP_VOLUME_AND_OFF_TIME    (uint8_t)0x1D
#define BEEP_AND_TONE_CONFIG        (uint8_t)0x1E
#define TONE_CONTROL                (uint8_t)0x1F
#define MASTER_VOLUME_CONTROL_A     (uint8_t)0x20
#define MASTER_VOLUME_CONTROL_B     (uint8_t)0x21
#define HEADPHONE_VOLUME_CONTROL_A  (uint8_t)0x22
#define HEADPHONE_VOLUME_CONTROL_B  (uint8_t)0x23
#define SPEAKER_VOLUME_CONTROL_A    (uint8_t)0x24
#define SPEAKER_VOLUME_CONTROL_B    (uint8_t)0x25
#define PCM_CHANNEL_SWAP            (uint8_t)0x26
#define LIMITER_CONTROL_1           (uint8_t)0x27
#define LIMITER_CONTROL_2           (uint8_t)0x28
#define LIMITER_ATTACK_RATE         (uint8_t)0x29
#define STATUS                      (uint8_t)0x2E
#define BATTERY_COMPENSATION        (uint8_t)0x2F
#define VP_BATTERY_LEVEL            (uint8_t)0x30
#define SPEAKER_STATUS              (uint8_t)0x31
#define TEMPERATURE_MONITOR_CONTROL (uint8_t)0x32
#define THERMAL_FOLDBACK            (uint8_t)0x33
#define CHARGE_PUMP_FREQUENCY       (uint8_t)0x34

void CS43L22_GPIO_Init()
{
	/* GPIOA (I2S_WS signal)
	 * GPIOB (I2C_SDA & I2C_SCL)
	 * GPIOC (I2S_MCK, I2S_SCK, I2S_SD)
	 * GPIOD (Reset pin on CS43L22)
	 */
	RCC->AHB1ENR |= (0xF<<0);	//GPIO clock enable
	
	/* Configure I2S pins - WS(PA4), MCK(PC7), SCK(PC10) & SD(PC12) */
	GPIOA->MODER |= (2<<8);												//Alternate function mode
	GPIOC->MODER |= (2<<14) | (2<<20) | (2<<24);	//Alternate function mode
	GPIOA->OSPEEDR |= (3<<8);											//Very high speed
	GPIOC->OSPEEDR |= (3<<14) | (3<<20) | (3<<24);//Very high speed
	GPIOA->OTYPER &= ~(1<<4);											//Push pull
	GPIOC->OTYPER &= ~(1<<7);											//Push pull
	GPIOC->OTYPER &= ~(1<<10);										//Push pull
	GPIOC->OTYPER &= ~(1<<12);										//Push pull
	GPIOA->PUPDR &= ~(3<<8);											//No pull
	GPIOC->PUPDR &= ~(3<<14);											//No pull
	GPIOC->PUPDR &= ~(3<<20);											//No pull
	GPIOC->PUPDR &= ~(3<<24);											//No pull
	GPIOA->AFR[0] |= (6<<24);											//AF6 - I2S3/SPI3
	GPIOC->AFR[0] |= (6<<28);											//AF6 - I2S3/SPI3
	GPIOC->AFR[1] |= (6<<8);											//AF6 - I2S3/SPI3
	GPIOC->AFR[1] |= (6<<16);											//AF6 - I2S3/SPI3
	
	/* Configure I2C pins - SCL(PB6) &  SDA(PB9) */
	GPIOB->MODER |= (2<<12);	 	//Alternate function mode
	GPIOB->MODER |= (2<<18);
	GPIOB->OSPEEDR |= (2<<12);	//High speed
	GPIOB->OSPEEDR |= (2<<18);
	GPIOB->OTYPER |= (1<<6);		//Open drain
	GPIOB->OTYPER |= (1<<9);
	GPIOB->PUPDR |= (1<<12);		//Pull up
	GPIOB->PUPDR |= (1<<18);
	GPIOB->AFR[0] |= (4<<24);						//AF4 - I2C1
	GPIOB->AFR[1] |= (4<<4);						//AF4 - I2C1
	
	/* Configure Reset pin - PD4 */
	GPIOD->MODER |= (1<<8);		//Output
	GPIOD->OSPEEDR |= (1<<8);	//Medium speed
	GPIOD->OTYPER &= ~(1<<4); //Push pull
	GPIOD->PUPDR |= (2<<8); 	//Pull down
}

void LED_GPIO_Init()
{
	RCC->AHB1ENR |= (1<<3);
	GPIOD->MODER |= (0x55<<24);
}

void LED_On(int ld)
{
	GPIOD->BSRR |= (1<<ld);
}

void LED_Off(int ld)
{
	GPIOD->BSRR |= (1<<(ld+16));
}

void LED_Toggle(int ld)
{
	for (int i = 0; i < 3; i++) {
		LED_On(ld);
		for (int j = 0; j < 500000; j++) {};
		LED_Off(ld);
		for (int j = 0; j < 500000; j++) {};
	}
}

void CS43L22_I2C1_Init()
{
	RCC->APB1ENR |= (1<<21);	//I2C1 clock enable
	I2C1->OAR1 |= (0x63<<1);	//I2C1 own address
	I2C1->CR2 |= 16;					//I2C frequency is 16MHz
	I2C1->CR1 |= (1<<10);			//Acknowledge enable
	I2C1->CCR |= (1<<15);			//I2C1 fast mode
	I2C1->CCR &= ~(1<<14);		//FM mode duty cycle - 2
	I2C1->CCR |= 0xA0;				//I2C1 frequency - 100KHz
	I2C1->CR1 |= (1<<0);			//I2C1 peripheral enable
}

void CS43L22_I2S3_Init()
{
	RCC->APB1ENR |= (1<<15);	//I2S3 clock enable
	//I2SPLL
	SPI3->I2SCFGR &= ~(1<<0);	//Channel length - 16bits
	SPI3->I2SCFGR &= ~(3<<1);	//Data length - 16bits
	SPI3->I2SCFGR &= ~(1<<3); //Clock polartiy low
	SPI3->I2SCFGR &= ~(3<<4); //I2S Philips standard
	SPI3->I2SCFGR |= (2<<8);  //I2S Mode - Master Tx
	SPI3->I2SCFGR |= (1<<11); //I2S mode selected
	SPI3->I2SPR |= (1<<9); 		//Master clock output enable 
	SPI3->I2SCFGR |= (1<<10); //I2S Enable
}

void I2C1_WaitUntilPeripheralFree()
{
	while ((I2C1->SR2>>1) & 0x1);
}

void I2C1_WaitUntilTxRegEmpty()
{
	while (!((I2C1->SR1 >> 7) & 0x1));
}

void I2C1_WaitUntilRxRegNotEmpty()
{
	while (!((I2C1->SR1 >> 6) & 0x1));
}

void I2C1_GenerateSTART()
{
	I2C1->CR1 |= (1<<8);				//Generate START condition
	while (!(I2C1->SR1 & 0x1));	//Wait until start bit generated
	
	(void)I2C1->SR1;						//Clear SB bit by reading SR1
}

void I2C1_Send7bitAddressW(uint8_t addr)
{
	I2C1->DR = (addr<<1);								//Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C1->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C1_Send7bitAddressR(uint8_t addr)
{
	I2C1->DR = (addr<<1) | 0x1;				//Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C1->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C1_GenerateStop()
{
	//while (!((I2C1->SR1 >> 2) & 0x1));	//Wait for BTF flag
	I2C1->CR1 |= (1<<9);								//Generate STOP condition
}

void I2C1_Set_DR(uint8_t data)
{
	I2C1->DR = data;
}

uint8_t I2C1_Get_DR()
{
	uint8_t data = I2C1->DR;
	return data;
}

void CS43L22_I2C1_Write(uint8_t device_addr, uint8_t MAP_byte, uint8_t data)
{
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressW(device_addr);
	
	I2C1_WaitUntilTxRegEmpty();							//Send MAP byte, auto-increment off
	I2C1_Set_DR(MAP_byte);
	
	I2C1_WaitUntilTxRegEmpty();							//Send data to be written
	I2C1_Set_DR(data);
	
	I2C1_GenerateStop();
}

uint8_t CS43L22_I2C1_AbortedWrite(uint8_t device_addr, uint8_t MAP_byte)
{
	uint8_t rec_data;
	
	/* Read a particular register by aborted write method */
	I2C1_WaitUntilPeripheralFree();					//Wait until the BUSY bit is cleared
	I2C1_GenerateSTART();										//Generate START condition
	
	I2C1_Send7bitAddressW(device_addr);			//Send device address, with W bit
	
	I2C1_WaitUntilTxRegEmpty();					//Send MAP byte, auto-increment off
	I2C1_Set_DR(MAP_byte);
	
	I2C1_GenerateStop();
	
	I2C1_GenerateSTART();
	
	I2C1_Send7bitAddressR(device_addr);			//Send the device address, with R bit
	
	I2C1_WaitUntilRxRegNotEmpty();
	rec_data = I2C1_Get_DR();
	
	I2C1_GenerateStop();
	
	return rec_data;
}

void I2S3_SendData(uint16_t data)
{
	while (!((SPI3->SR >> 1) & 0x1));	//Wait until Tx buffer empty
	SPI3->DR = data;
}

void GPIO_SetPin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	gpio_td->BSRR |= (1<<gpio_pin);
}

void GPIO_ResetPin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	gpio_td->BSRR |= (1<<(16 + gpio_pin));
}

void GPIO_TogglePin(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	/* If pin is HIGH, set to LOW */
	if ((gpio_td->ODR >> gpio_pin) & 0x1) {
		gpio_td->ODR &= ~(1<<gpio_pin);
	}
	
	/* else if pin if LOW, set to HIGH */
	else {
		gpio_td->ODR |= (1<<gpio_pin);
	}
}

void GPIO_Toggle2_With_Delay(GPIO_TypeDef *gpio_td, uint8_t gpio_pin)
{
	GPIO_TogglePin(gpio_td, gpio_pin);
	
	for (int i = 0; i < 500000; i++) {
		/* Delay */
	}
	
	GPIO_TogglePin(gpio_td, gpio_pin);
}

void CS43L22_PowerUp()
{
	/* 1. Reset CS43L22 by toggling PD4 */
	GPIO_SetPin(GPIOD, 4);
		
	/* 2. Start MCLK with appropriate frequency - MCLK 12Mhz, Sample rate 8.000 */
	uint8_t clock_settings = 0;
	clock_settings &= ~(1<<0);	//MCLK Divide By 2
	clock_settings |= (1<<1);		//Internal MCLK/LRCK Ratio
	clock_settings &= ~(1<<3);	//27 MHz Video Clock
	clock_settings |= (1<<4);		//32kHz Sample Rate Group
	clock_settings |= (3<<5);		//Speed Mode
	CS43L22_I2C1_Write(CS43L22_DEVICE_ADDR, CLOCKING_CONTROL, clock_settings);
	
	/* 3. Set POWER_CONTROL_1 register to 0x9E */
	CS43L22_I2C1_Write(CS43L22_DEVICE_ADDR, POWER_CONTROL_1, 0x9E);
	
	/* 4. Apply WS, SCLK and SDIN for normal operation to begin */
	CS43L22_I2S3_Init();
}

void CS43L22_PowerDown()
{
	/* 1. Mute the DACs */
	
	/* 2. Set POWER_CONTROL_1 register to 0x02 */
	CS43L22_I2C1_Write(CS43L22_DEVICE_ADDR, POWER_CONTROL_1, 0x02);
	
	/* 3. Set ~RESET to LOW */
	GPIO_ResetPin(GPIOD, 4);
}

void CS43L22_Configure()
{
	/* Interface control 1*/
	uint8_t ic1_data = 0;
	ic1_data |= (1<<2);		//DAC Interface Format - I2S
	ic1_data &= ~(1<<7);	//Slave(input only)
	CS43L22_I2C1_Write(CS43L22_DEVICE_ADDR, INTERFACE_CONTROL_1, ic1_data);
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

void CS43L22_Master_Volume_Control()
{
}

int main(void)
{
	/* CS43L22 - I2C(Control) & I2S(Audio) */
	CS43L22_GPIO_Init();
	LED_GPIO_Init();
	CS43L22_I2C1_Init();
	CS43L22_PowerUp();
	CS43L22_Configure();
	
	/* Read Chip ID */
	uint8_t chip_id = CS43L22_I2C1_AbortedWrite(CS43L22_DEVICE_ADDR, CHIP_ID_REG);
	if ((chip_id>>3) == 0x1C) {
		LED_Toggle(12);
	}
	else {
		LED_On(14);
		goto stop;
	}
	
	/* Beep Generator */
	
	stop: while (1) {
	}
	
	return 0;
}
