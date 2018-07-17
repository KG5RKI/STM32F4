#include "stm32f4xx.h"                  // Device header
#include "my_gpio.h"

void I2C1_GPIO_Init() {
	/* PB6 - I2C1_SCL, PB7 - I2C1_SDA */
	
	/* Enable GPIOB clock */
	RCC->AHB1ENR |= (1<<1);
	
	/* Set pins' mode to alternate function */
	GPIOB->MODER |= (GPIO_MODE_AF << 12);
	GPIOB->MODER |= (GPIO_MODE_AF << 14);
	
	/* Set output type to open drain */
	GPIOB->OTYPER |= (GPIO_OTYPE_OD << 6);
	GPIOB->OTYPER |= (GPIO_OTYPE_OD << 7);
	
	/* Set output speed to high */
	GPIOB->OSPEEDR |= (GPIO_SPEED_HIGH << 12);
	GPIOB->OSPEEDR |= (GPIO_SPEED_HIGH << 14);
	
	/* Enable pull-up resistors */
	GPIOB->PUPDR |= (GPIO_PULL_UP << 12);
	GPIOB->PUPDR |= (GPIO_PULL_UP << 14);
}

void I2C1_Init() {
	
	/* Enable I2C1 GPIOs */
	I2C1_GPIO_Init();
	
	/* Enable I2C1 clock */
	RCC->APB1ENR |= (1 << 21);
	
	/* Set peripheral clock frequenecy to 16MHz */
	I2C1->CR2 |= 16;
	
	/* Set mode to SM(Standard Mode) */
	I2C1->CCR &= ~(1 << 15);
	
	/* Set I2C1_SCL frequency to 100KHz */
	
	
	/* I2C1 peripheral enable */
	I2C1->CR1 |= (1 << 0);
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

void I2C1_Write_1ByteData(uint8_t DEVICE_ADDR, uint8_t FIRST_WORD_ADDR, uint8_t SECOND_WORD_ADDR, uint8_t data) {
	
	//I2C1_WaitUntilPeripheralFree();
	
	/* Generate START condition */
	I2C1_GenerateSTART();
	
	/* Send device address */
	I2C1_Send7bitAddressW(DEVICE_ADDR);
	
	/* Send memory address to be written */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(FIRST_WORD_ADDR);
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(SECOND_WORD_ADDR);
	
	/* Send data to be stored */
	I2C1_WaitUntilBTF();
	I2C1_Set_DR(data);
	
	/* Generate STOP condition */
	I2C1_GenerateStop();
}

void I2C1_Write_Data(uint8_t DEVICE_ADDR, uint8_t FIRST_WORD_ADDR, uint8_t SECOND_WORD_ADDR, uint8_t *data, int data_items) {
	//TODO
}

uint8_t I2C1_Read_1ByteData(uint8_t DEVICE_ADDR, uint8_t FIRST_WORD_ADDR, uint8_t SECOND_WORD_ADDR) {
	uint8_t data;
	
	//I2C1_WaitUntilPeripheralFree();
	
	/* Generate START condition */
	I2C1_GenerateSTART();
	
	I2C1_Send7bitAddressR(DEVICE_ADDR);
	
	/* Send memory address from where data has to be read */
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(FIRST_WORD_ADDR);
	I2C1_WaitUntilTxRegEmpty();
	I2C1_Set_DR(SECOND_WORD_ADDR);

	I2C1_WaitUntilRxRegNotEmpty();
	data = I2C1_Get_DR();
	
	/* Generate STOP condition */
	I2C1_GenerateStop();
	return data;
}
