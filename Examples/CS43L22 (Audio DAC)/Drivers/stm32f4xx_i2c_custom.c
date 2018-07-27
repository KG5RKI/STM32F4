#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2c_custom.h"

void I2C1_GPIO_Init()
{
	/* Configure I2C pins - SCL(PB6) &  SDA(PB9) */
	
	GPIO_ClockInit(GPIOB);
	GPIO_Config(GPIOB, 6, GPIO_MODE_ALTERNATE, GPIO_OTYPE_OD, GPIO_OSPEED_FAST, GPIO_PULL_UP);
	GPIO_Config(GPIOB, 9, GPIO_MODE_ALTERNATE, GPIO_OTYPE_OD, GPIO_OSPEED_FAST, GPIO_PULL_UP);
	GPIO_Config_AF(GPIOB, 6, GPIO_AF4);
	GPIO_Config_AF(GPIOB, 9, GPIO_AF4);
}

void I2C1_Init()
{
	I2C1_GPIO_Init();
	
	RCC->APB1ENR |= (1<<21); //Enable I2C1 clock
	I2C1->OAR1 |= (0x63<<1); //I2C1 own address
	I2C1->CR2 |= 16; //I2C frequency is 16MHz
	I2C1->CR1 |= (1<<10); //Acknowledge enable
	I2C1->CCR |= (1<<15); //I2C1 fast mode
	I2C1->CCR &= ~(1<<14); //FM mode duty cycle - 2
	I2C1->CCR |= 0xA0; //I2C1 frequency - 100KHz
	I2C1->CR1 |= (1<<0); //I2C1 peripheral enable
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

void I2C1_WaitUntilBTF()
{
	while (!((I2C1->SR1>>2) & 0x1));
}

void I2C1_GenerateSTART()
{
	I2C1->CR1 |= (1<<8); //Generate START condition
	while (!(I2C1->SR1 & 0x1)); //Wait until start bit generated
	
	(void)I2C1->SR1; //Clear SB bit by reading SR1
}

void I2C1_Send7bitAddressW(uint8_t addr)
{
	I2C1->DR = (addr<<1); //Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1)); //Wait until address is sent
	
	(void)I2C1->SR1; //Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C1_Send7bitAddressR(uint8_t addr)
{
	I2C1->DR = (addr<<1) | 0x1; //Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1)); //Wait until address is sent
	
	(void)I2C1->SR1; //Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C1_GenerateStop()
{
	//while (!((I2C1->SR1 >> 2) & 0x1)); //Wait for BTF flag
	I2C1->CR1 |= (1<<9); //Generate STOP condition
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

void I2C1_Write(uint8_t device_addr, uint8_t MAP_byte, uint8_t data)
{
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressW(device_addr);
	I2C1_WaitUntilTxRegEmpty(); //Send MAP byte, auto-increment off
	I2C1_Set_DR(MAP_byte);
	I2C1_WaitUntilBTF(); //Send data to be written
	I2C1_Set_DR(data);
	I2C1_GenerateStop();
}

uint8_t I2C1_Read(uint8_t device_addr, uint8_t MAP_byte)
{
	uint8_t rec_data;
	
	/* Read a particular register by aborted write method */
	I2C1_WaitUntilPeripheralFree(); //Wait until the BUSY bit is cleared
	I2C1_GenerateSTART(); //Generate START condition
	I2C1_Send7bitAddressW(device_addr);//Send device address, with W bit
	I2C1_WaitUntilTxRegEmpty(); //Send MAP byte, auto-increment off
	I2C1_Set_DR(MAP_byte);
	I2C1_GenerateStop();
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressR(device_addr); //Send the device address, with R bit
	I2C1_WaitUntilRxRegNotEmpty();
	rec_data = I2C1_Get_DR();
	I2C1_GenerateStop();
	
	return rec_data;
}
