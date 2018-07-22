#include "stm32f4xx.h"                  // Device header

#include "my_gpio.h"
#include "my_i2c.h"

#include "stdlib.h"

void I2C1_GPIO_Init() {
	/* PB6 - I2C1_SCL, PB9 - I2C1_SDA */
	
	/* Enable GPIOB clock */
	RCC->AHB1ENR |= (1<<1);
	
	/* Set pins' mode to alternate function */
	GPIOB->MODER |= (GPIO_MODE_AF << 12);
	GPIOB->MODER |= (GPIO_MODE_AF << 18);
	
	/* Set output type to open drain */
	GPIOB->OTYPER |= (GPIO_OTYPE_OD << 6);
	GPIOB->OTYPER |= (GPIO_OTYPE_OD << 9);
	
	/* Set output speed to high */
	GPIOB->OSPEEDR |= (GPIO_SPEED_HIGH << 12);
	GPIOB->OSPEEDR |= (GPIO_SPEED_HIGH << 18);
	
	/* Enable pull-up resistors */
	GPIOB->PUPDR |= (GPIO_PULL_UP << 12);
	GPIOB->PUPDR |= (GPIO_PULL_UP << 18);
	
	/* Configure GPIO pins, for alternate function */
	GPIOB->AFR[0] |= (4 << 24);
	GPIOB->AFR[1] |= (4 << 4);
}

void I2C1_Init() {
	
	/* Enable I2C1 GPIOs */
	I2C1_GPIO_Init();
	
	/* Enable I2C1 clock */
	RCC->APB1ENR |= (1 << 21);
	
	/* Set peripheral clock frequenecy to 16MHz */
	I2C1->CR2 |= 16;
	
	/* Set I2C1_SCL frequency to 100KHz */
	I2C1->CCR |= 0x28;
	
	/* I2C1 peripheral enable */
	I2C1->CR1 |= (1 << 0);
	
	I2C1_ACK_En();
}

void I2C1_SoftwareReset()
{
	I2C1->CR1 |= (1 << 15);
}

void I2C1_ACK_En() {
	I2C1->CR1 |= (1 << 10);
}

void I2C1_ACK_Dis() {
	I2C1->CR1 &= ~(1 << 10);
}

void I2C1_WaitUntilPeripheralFree() {
	while ((I2C1->SR2>>1) & 0x1);
}

void I2C1_WaitUntilTxRegEmpty() {
	while (!((I2C1->SR1 >> 7) & 0x1));
}

void I2C1_WaitUntilRxRegNotEmpty() {
	while (!((I2C1->SR1 >> 6) & 0x1));
}

void I2C1_WaitUntilBTF() {
	while (!((I2C1->SR1>>2) & 0x1));
}

void I2C1_GenerateSTART() {
	/* Generate START condition */
	I2C1->CR1 |= (1<<8);
	
	/* Wait until start bit generated */
	while (!(I2C1->SR1 & 0x1));
	
	/* Clear SB bit by reading SR1 */
	(void)I2C1->SR1;
}

void I2C1_Send7bitAddressW(uint8_t addr) {
	I2C1->DR = (addr<<1);
	
	/* Wait until address is sent */
	while (!((I2C1->SR1 >> 1) & 0x1));
	
	/* Clear SB bit by reading SR1 & SR2 */
	(void)I2C1->SR1;
	(void)I2C1->SR2;
}

void I2C1_Send7bitAddressR(uint8_t addr) {
	I2C1->DR = (addr<<1) | 0x1;
	
	/* Wait until address is sent */
	while (!((I2C1->SR1 >> 1) & 0x1));
	
	/* Clear SB bit by reading SR1 & SR2 */
	(void)I2C1->SR1;
	(void)I2C1->SR2;
}

void I2C1_GenerateStop() {
	/* Wait for BTF flag */
	//while (!((I2C1->SR1 >> 2) & 0x1));
	
	/* Generate STOP condition */
	I2C1->CR1 |= (1<<9);
}

void I2C1_Set_DR(uint8_t data) {
	I2C1->DR = data;
}

uint8_t I2C1_Get_DR() {
	uint8_t data = I2C1->DR;
	return data;
}

void EEPROM_256K_I2C1_Byte_Write(uint8_t DEVICE_ADDR, uint16_t MEM_ADDR, uint8_t data)
{
	uint8_t mem_addr_1 = (uint8_t) MEM_ADDR & 0xFF;
	uint8_t mem_addr_2 = (uint8_t) ((MEM_ADDR >> 8) & 0xFF);
	
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressW(DEVICE_ADDR);
	
	/* Send first & second word address */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_1);
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_2);
	
	/* Send data */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(data);
	
	//I2C1_WaitUntilBTF();
	I2C1_GenerateStop();
}

void EEPROM_256K_I2C1_64Byte_Page_Write(uint8_t DEVICE_ADDR, uint8_t *data)
{
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressW(DEVICE_ADDR);
	
	for (uint8_t *pd = data; pd < (data + 64); pd++) {
		I2C1_WaitUntilTxRegEmpty();
		I2C1_Set_DR(*pd);
	}
	
	I2C1_WaitUntilBTF();
	I2C1_GenerateStop();
}


uint8_t EEPROM_256K_I2C1_Current_Read(uint8_t DEVICE_ADDR)
{
	uint8_t read_data;
	
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressR(DEVICE_ADDR);
	
	I2C1_WaitUntilRxRegNotEmpty();
	read_data = I2C1_Get_DR();
	
	I2C1_GenerateStop();
	return read_data;
}

uint8_t EEPROM_256K_I2C1_Random_Read(uint8_t DEVICE_ADDR, uint16_t MEM_ADDR)
{
	uint8_t read_data;
	uint8_t mem_addr_1 = (uint8_t) MEM_ADDR & 0xFF;
	uint8_t mem_addr_2 = (uint8_t) ((MEM_ADDR >> 8) & 0xFF);
	
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressW(DEVICE_ADDR);
	
	/* Send first word address */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_1);
	
	/* Send second word address */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_2);
	
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressR(DEVICE_ADDR);
	
	I2C1_WaitUntilRxRegNotEmpty();
	read_data = I2C1_Get_DR();
	
	I2C1_GenerateStop();
	return read_data;
}

void EEPROM_256K_I2C1_Sequential_Read(uint8_t DEVICE_ADDR, uint16_t MEM_ADDR, uint8_t *loc, int N)
{
	I2C1_GenerateSTART();
	
	I2C1_Send7bitAddressW(DEVICE_ADDR);
	
	uint8_t mem_addr_1 = (uint8_t) MEM_ADDR & 0xFF;
	uint8_t mem_addr_2 = (uint8_t) ((MEM_ADDR >> 8) & 0xFF);
	
	/* Send first word address */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_1);
	
	/* Send second word address */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(mem_addr_2);
	
	I2C1_GenerateSTART();
	I2C1_Send7bitAddressR(DEVICE_ADDR);
	
	for (int i = 0; i < N; i++, loc++) {
		I2C1_WaitUntilRxRegNotEmpty();
		*loc = I2C1_Get_DR();
	}
	
	I2C1_GenerateStop();
}
