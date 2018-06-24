#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_i2c.h"

#include <stdbool.h>

/* Define GPIO macros */
#define INPUT  		0x0
#define OUTPUT 		0x1
#define ALT_FUNC	0x2
#define ANALOG 		0x3

#define PUSH_PULL  0x0
#define OPEN_DRAIN 0x1

#define LOW_SPEED       0x0
#define MEDIUM_SPEED    0x1
#define HIGH_SPEED      0x2
#define VERY_HIGH_SPEED 0x3

#define NO_PULL   0x0
#define PULL_UP   0x1
#define PULL_DOWN 0x2

#define AF4 0x4

void I2C1_GPIO_Init()
{
	/* SCL - PB6, SDA - PB7 */
	
	/* Enable GPIOB clock */
	RCC -> AHB1ENR |= (1<<1);
	
	/* Set pin mode to AF (Alternate Function) */ 
	GPIOB->MODER |= (ALT_FUNC<<12);
	GPIOB->MODER |= (ALT_FUNC<<14);
	
	/* Set output type to open-drain */
	GPIOB->OTYPER |= (1<<6);
	GPIOB->OTYPER |= (1<<7);
	
	/* Set output speed to high speed */
	GPIOB->OSPEEDR |= (HIGH_SPEED<<12);
	GPIOB->OSPEEDR |= (HIGH_SPEED<<14);
	
	/* Enable pull-up resistors */
	GPIOB->PUPDR |= (PULL_UP<<12);
	GPIOB->PUPDR |= (PULL_UP<<14);
	
	/* Select alternate function */
	GPIOB->AFR[0] = (AF4<<24);
	GPIOB->AFR[0] = (AF4<<28);
}

void I2C2_GPIO_Init()
{
	/* SCL - PB10, SDA - PB11 */
	
	/* Enable GPIOB clock */
	RCC -> AHB1ENR |= (1<<1);
	
	/* Set pin mode to AF (Alternate Function) */ 
	GPIOB->MODER |= (ALT_FUNC<<20);
	GPIOB->MODER |= (ALT_FUNC<<22);
	
	/* Set output type to open-drain */
	GPIOB->OTYPER |= (1<<10);
	GPIOB->OTYPER |= (1<<11);
	
	/* Set output speed to high speed */
	GPIOB->OSPEEDR |= (HIGH_SPEED<<20);
	GPIOB->OSPEEDR |= (HIGH_SPEED<<22);
	
	/* Enable pull-up resistors */
	GPIOB->PUPDR |= (PULL_UP<<20);
	GPIOB->PUPDR |= (PULL_UP<<22);
	
	/* Select alternate function */
	GPIOB->AFR[1] = (AF4<<8);
	GPIOB->AFR[1] = (AF4<<12);
}

void I2C3_GPIO_Init()
{
	/* SCL - PA8, SDA - PC9 */
	
	/* Enable GPIOA & GPIOC clock */
	RCC -> AHB1ENR |= (1<<0);
	RCC -> AHB1ENR |= (1<<2);
	
	/* Set pin mode to AF (Alternate Function) */ 
	GPIOA->MODER |= (ALT_FUNC<<16);
	GPIOC->MODER |= (ALT_FUNC<<18);
	
	/* Set output type to open-drain */
	GPIOA->OTYPER |= (1<<8);
	GPIOC->OTYPER |= (1<<9);
	
	/* Set output speed to high speed */
	GPIOA->OSPEEDR |= (HIGH_SPEED<<16);
	GPIOC->OSPEEDR |= (HIGH_SPEED<<18);
	
	/* Enable pull-up resistors */
	GPIOA->PUPDR |= (PULL_UP<<16);
	GPIOC->PUPDR |= (PULL_UP<<18);
	
	/* Select alternate function */
	GPIOB->AFR[1] = (AF4<<0);
	GPIOB->AFR[1] = (AF4<<4);
}

void I2C1_Init(_Bool ENGC, uint8_t FREQ)
{
	/* Enable I2C1 GPIO pins */
	I2C1_GPIO_Init();
	
	/* Enable I2C1 peripheral clock */
	RCC->APB1ENR |= (1<<21);
	
	/* Configure general call */
	I2C1->CR1 = (ENGC==1) ? (I2C1->CR1 | (1<<6)) : (I2C1->CR1 & ~(1<<6));
	
	/* Configure I2C1 peripheral frequency */
	if ((FREQ >= 2) && (FREQ <= 16)) {
		I2C1->CR2 = FREQ;
	}
	else {
		I2C1->CR2 = 16;
	}
	
	/* Standard Mode - default */
	
	/* Set Serial Clock(SCL) frequency - 100kHz */
	I2C1->CCR |= 0xA9;
}

void I2C2_Init(_Bool ENGC, uint8_t FREQ)
{
	/* Enable I2C2 GPIO pins */
	I2C2_GPIO_Init();
	
	/* Configure I2C2 peripheral clock */
	RCC->APB1ENR |= (1<<22);
	
	/* Configure general call */
	I2C2->CR1 = (ENGC==1) ? (I2C2->CR1 | (1<<6)) : (I2C2->CR1 & ~(1<<6));
	
	/* Configure I2C2 peripheral frequency */
	if ((FREQ >= 2) && (FREQ <= 16)) {
		I2C2->CR2 = FREQ;
	}
	else {
		I2C2->CR2 = 16;
	}
	
	/* Standard Mode - default */
	
	/* Set Serial Clock(SCL) frequency - 100kHz */
	I2C2->CCR |= 0xA9;
}

void I2C3_Init(_Bool ENGC, uint8_t FREQ)
{
	/* Enable I2C3 GPIO pins */
	I2C3_GPIO_Init();
	
	/* Configure I2C3 peripheral clock */
	RCC->APB1ENR |= (1<<23);
	
	/* Configure general call */
	I2C3->CR1 = (ENGC==1) ? (I2C3->CR1 | (1<<6)) : (I2C3->CR1 & ~(1<<6));
	
	/* Configure I2C3 peripheral frequency */
	if ((FREQ >= 2) && (FREQ <= 16)) {
		I2C3->CR2 = FREQ;
	}
	else {
		I2C3->CR2 = 16;
	}
	
	/* Standard Mode - default */
	
	/* Set Serial Clock(SCL) frequency - 100kHz */
	I2C3->CCR |= 0xA9;
}

void I2Cx_Init(I2Cx n, _Bool ENGC, uint8_t FREQ)
{
	switch (n) {
		case I2C_1: I2C1_Init(ENGC, FREQ);
		case I2C_2: I2C2_Init(ENGC, FREQ);
		case I2C_3: I2C3_Init(ENGC, FREQ);
	}
}

void I2C1_Slave_Init(_Bool NOSTRETCH, _Bool ENGC, uint8_t FREQ, uint16_t OA)
{
	I2Cx_Init(I2C_1, ENGC, FREQ);
	
	/* Configure clock stretching */
	I2C1->CR1 = (NOSTRETCH==1) ? (I2C1->CR1 | (1<<7)) : (I2C1->CR1 & ~(1<<7));
	
	/* Set own address */
	if (OA > 0x7F) {
		/* 10-bit addressing mode */
	}
	else {
		I2C1->OAR1 &= ~(1<<15);
		I2C1->OAR1 |= (OA<<1);
	}
}

void I2C2_Slave_Init(_Bool NOSTRETCH, _Bool ENGC, uint8_t FREQ, uint16_t OA)
{
	I2Cx_Init(I2C_2, ENGC, FREQ);
	
	/* Configure clock stretching */
	I2C2->CR1 = (NOSTRETCH==1) ? (I2C2->CR1 | (1<<7)) : (I2C2->CR1 & ~(1<<7));
	
	/* Set own address */
	if (OA > 0x7F) {
		/* 10-bit addressing mode */
	}
	else {
		I2C2->OAR1 &= ~(1<<15);
		I2C2->OAR1 |= (OA<<1);
	}
}

void I2C3_Slave_Init(_Bool NOSTRETCH, _Bool ENGC, uint8_t FREQ, uint16_t OA)
{
	I2Cx_Init(I2C_3, ENGC, FREQ);
	
	/* Configure clock stretching */
	I2C3->CR1 = (NOSTRETCH==1) ? (I2C3->CR1 | (1<<7)) : (I2C3->CR1 & ~(1<<7));
	
	/* Set own address */
	if (OA > 0x7F) {
		/* 10-bit addressing mode */
	}
	else {
		I2C3->OAR1 &= ~(1<<15);
		I2C3->OAR1 |= (OA<<1);
	}
}

void I2Cx_Slave_Init(I2Cx n, _Bool NOSTRETCH, _Bool ENGC, uint8_t FREQ, uint16_t OA)
{
	switch (n) {
		case I2C_1: I2C1_Slave_Init(NOSTRETCH, ENGC, FREQ, OA);
		case I2C_2: I2C2_Slave_Init(NOSTRETCH, ENGC, FREQ, OA);
		case I2C_3: I2C3_Slave_Init(NOSTRETCH, ENGC, FREQ, OA);
	}
}

void I2C1_En()
{
	I2C1->CR1 |= (1<<0);
}

void I2C2_En()
{
	I2C2->CR1 |= (1<<0);
}

void I2C3_En()
{
	I2C3->CR1 |= (1<<0);
}

void I2Cx_En(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_En(); break;
		case I2C_2: I2C2_En(); break;
		case I2C_3: I2C3_En(); break;
	}
}

void I2C1_Dis()
{
	I2C1->CR1 &= ~(1<<0);
}

void I2C2_Dis()
{
	I2C2->CR1 &= ~(1<<0);
}

void I2C3_Dis()
{
	I2C3->CR1 &= ~(1<<0);
}

void I2Cx_Dis(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_Dis(); break;
		case I2C_2: I2C2_Dis(); break;
		case I2C_3: I2C3_Dis(); break;
	}
}

void I2C1_ACK_En()
{
	I2C1->CR1 |= (1<<10);
}

void I2C2_ACK_En()
{
	I2C2->CR1 |= (1<<10);
}

void I2C3_ACK_En()
{
	I2C3->CR1 |= (1<<10);
}

void I2Cx_ACK_En(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_ACK_En(); break;
		case I2C_2: I2C2_ACK_En(); break;
		case I2C_3: I2C3_ACK_En(); break;
	}
}

void I2C1_ACK_Dis()
{
	I2C1->CR1 &= ~(1<<10);
}

void I2C2_ACK_Dis()
{
	I2C2->CR1 &= ~(1<<10);
}

void I2C3_ACK_Dis()
{
	I2C3->CR1 &= ~(1<<10);
}

void I2Cx_ACK_Dis(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_ACK_Dis(); break;
		case I2C_2: I2C2_ACK_Dis(); break;
		case I2C_3: I2C3_ACK_Dis(); break;
	}
}

void I2C1_GenerateSTART()
{
	I2C1->CR1 |= (1<<8);				//Generate START condition
	while (!(I2C1->SR1 & 0x1));	//Wait until start bit generated
	
	(void)I2C1->SR1;						//Clear SB bit by reading SR1
}

void I2C2_GenerateSTART()
{
	I2C2->CR1 |= (1<<8);				//Generate START condition
	while (!(I2C2->SR1 & 0x1));	//Wait until start bit generated
	
	(void)I2C2->SR1;						//Clear SB bit by reading SR1
}

void I2C3_GenerateSTART()
{
	I2C3->CR1 |= (1<<8);				//Generate START condition
	while (!(I2C3->SR1 & 0x1));	//Wait until start bit generated
	
	(void)I2C3->SR1;						//Clear SB bit by reading SR1
}

void I2Cx_GenerateSTART(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_GenerateSTART(); break;
		case I2C_2: I2C2_GenerateSTART(); break;
		case I2C_3: I2C3_GenerateSTART(); break;
	}
}

void I2C1_Send7bitAddressW(uint8_t addr)
{
	I2C1->DR |= (addr<<1) | 0x0;				//Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C1->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C2_Send7bitAddressW(uint8_t addr)
{
	I2C2->DR |= (addr<<1) | 0x0;				//Write address to I2C data register
	while (!((I2C2->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C2->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C2->SR2;
}

void I2C3_Send7bitAddressW(uint8_t addr)
{
	I2C3->DR |= (addr<<1) | 0x0;				//Write address to I2C data register
	while (!((I2C3->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C3->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C3->SR2;
}

void I2Cx_Send7bitAddressW(I2Cx n, uint8_t addr)
{
	switch (n) {
		case I2C_1: I2C1_Send7bitAddressW(addr); break;
		case I2C_2: I2C2_Send7bitAddressW(addr); break;
		case I2C_3: I2C3_Send7bitAddressW(addr); break;
	}
}

void I2C1_Send7bitAddressR(uint8_t addr)
{
	I2C1->DR |= (addr<<1) | 0x1;				//Write address to I2C data register
	while (!((I2C1->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C1->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C1->SR2;
}

void I2C2_Send7bitAddressR(uint8_t addr)
{
	I2C2->DR |= (addr<<1) | 0x1;				//Write address to I2C data register
	while (!((I2C2->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C2->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C2->SR2;
}

void I2C3_Send7bitAddressR(uint8_t addr)
{
	I2C3->DR |= (addr<<1) | 0x1;				//Write address to I2C data register
	while (!((I2C3->SR1 >> 1) & 0x1));	//Wait until address is sent
	
	(void)I2C3->SR1;										//Clear SB bit by reading SR1 & SR2
	(void)I2C3->SR2;
}

void I2Cx_Send7bitAddressR(I2Cx n, uint8_t addr)
{
	switch (n) {
		case I2C_1: I2C1_Send7bitAddressR(addr); break;
		case I2C_2: I2C2_Send7bitAddressR(addr); break;
		case I2C_3: I2C3_Send7bitAddressR(addr); break;
	}
}

void I2C1_Write_To_DR(uint8_t data)
{
	while (!((I2C1->SR1 >> 7) & 0x1));
	I2C1->DR = data;
}

void I2C2_Write_To_DR(uint8_t data)
{
	while (!((I2C2->SR1 >> 7) & 0x1));
	I2C2->DR = data;
}

void I2C3_Write_To_DR(uint8_t data)
{
	while (!((I2C3->SR1 >> 7) & 0x1));
	I2C3->DR = data;
}

void I2Cx_Write_To_DR(I2Cx n, uint8_t data)
{
	switch (n) {
		case I2C_1: I2C1_Write_To_DR(data); break;
		case I2C_2: I2C2_Write_To_DR(data); break;
		case I2C_3: I2C3_Write_To_DR(data); break;
	}
}

void I2C1_GenerateStop()
{
	while (!((I2C1->SR1 >> 2) & 0x1));	//Wait for BTF flag
	I2C1->CR1 |= (1<<9);								//Generate STOP condition
}

void I2C2_GenerateStop()
{
	while (!((I2C2->SR1 >> 2) & 0x1));	//Wait for BTF flag
	I2C2->CR1 |= (1<<9);								//Generate STOP condition
}

void I2C3_GenerateStop()
{
	while (!((I2C3->SR1 >> 2) & 0x1));	//Wait for BTF flag
	I2C3->CR1 |= (1<<9);								//Generate STOP condition
}

void I2Cx_GenerateStop(I2Cx n)
{
	switch (n) {
		case I2C_1: I2C1_GenerateStop(); break;
		case I2C_2: I2C2_GenerateStop(); break;
		case I2C_3: I2C3_GenerateStop(); break;
	}
}

void I2C1_Interrupt_En(I2C_Interrupt ie)
{
	switch (ie) {
		case SB:
		case ADDR:
		case ADD10:
		case STOPF:
		case BTF:
			I2C1->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C1_EV_IRQn);
			break;
		
		case RxNE:
		case TxE:
			I2C1->CR2 |= (1<<10);
			I2C1->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C1_EV_IRQn);
			break;
		
		case BERR:
		case ARLO:
		case AF:
		case OVR:
		case PECERR:
		case TIMEOUT:
		case SMBALERT:
			I2C1->CR2 |= (1<<8);
			NVIC_EnableIRQ(I2C1_ER_IRQn);
			break;
	}
}

void I2C2_Interrupt_En(I2C_Interrupt ie)
{
	switch (ie) {
		case SB:
		case ADDR:
		case ADD10:
		case STOPF:
		case BTF:
			I2C2->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C2_EV_IRQn);
			break;
		
		case RxNE:
		case TxE:
			I2C2->CR2 |= (1<<10);
			I2C2->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C2_EV_IRQn);
			break;
		
		case BERR:
		case ARLO:
		case AF:
		case OVR:
		case PECERR:
		case TIMEOUT:
		case SMBALERT:
			I2C2->CR2 |= (1<<8);
			NVIC_EnableIRQ(I2C2_ER_IRQn);
			break;
	}
}

void I2C3_Interrupt_En(I2C_Interrupt ie)
{
	switch (ie) {
		case SB:
		case ADDR:
		case ADD10:
		case STOPF:
		case BTF:
			I2C3->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C3_EV_IRQn);
			break;
		
		case RxNE:
		case TxE:
			I2C3->CR2 |= (1<<10);
			I2C3->CR2 |= (1<<9);
			NVIC_EnableIRQ(I2C3_EV_IRQn);
			break;
		
		case BERR:
		case ARLO:
		case AF:
		case OVR:
		case PECERR:
		case TIMEOUT:
		case SMBALERT:
			I2C3->CR2 |= (1<<8);
			NVIC_EnableIRQ(I2C3_ER_IRQn);
			break;
	}
}

void I2Cx_Interrupt_En(I2Cx n, I2C_Interrupt ie)
{
	switch (n) {
		case I2C_1: I2C1_Interrupt_En(ie);
		case I2C_2: I2C2_Interrupt_En(ie);
		case I2C_3: I2C3_Interrupt_En(ie);
	}
}

void I2C1_Master_Transmit(uint16_t addr, uint8_t *data, int N)
{
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_1);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressW(I2C_1, addr);
	}
	
	/* Transmit data */
	uint8_t *pdata = data;
	while (N > 0) {
		I2Cx_Write_To_DR(I2C_1, *pdata);
		pdata++;
		N--;
	}
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_1);
}

void I2C2_Master_Transmit(uint16_t addr, uint8_t *data, int N)
{
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_2);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressW(I2C_2, addr);
	}
	
	/* Transmit data */
	uint8_t *pdata = data;
	while (N > 0) {
		I2Cx_Write_To_DR(I2C_2, *pdata);
		pdata++;
		N--;
	}
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_2);
}

void I2C3_Master_Transmit(uint16_t addr, uint8_t *data, int N)
{
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_3);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressW(I2C_3, addr);
	}
	
	/* Transmit data */
	uint8_t *pdata = data;
	while (N > 0) {
		I2Cx_Write_To_DR(I2C_3, *pdata);
		pdata++;
		N--;
	}
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_3);
}

void I2Cx_Master_Transmit(I2Cx n, uint16_t addr, uint8_t *data, int N)
{
	switch (n) {
		case I2C_1: I2C1_Master_Transmit(addr, data, N);
		case I2C_2: I2C2_Master_Transmit(addr, data, N);
		case I2C_3: I2C3_Master_Transmit(addr, data, N);
	}
}

uint8_t I2C1_Read_From_DR()
{
	uint8_t data;
	while (1) {
		if ((I2C1->SR1>>6) & 0x1) {
			data = I2C1->DR;
			break;
		}
	}
	return data;
}

uint8_t I2C2_Read_From_DR()
{
	uint8_t data;
	while (1) {
		if ((I2C2->SR1>>6) & 0x1) {
			data = I2C2->DR;
			break;
		}
	}
	return data;
}

uint8_t I2C3_Read_From_DR()
{
	uint8_t data;
	while (1) {
		if ((I2C3->SR1>>6) & 0x1) {
			data = I2C3->DR;
			break;
		}
	}
	return data;
}

uint8_t I2Cx_Read_From_DR(I2Cx n)
{
	switch (n) {
		case I2C_1: return I2C1_Read_From_DR();
		case I2C_2: return I2C2_Read_From_DR();
		case I2C_3: return I2C3_Read_From_DR();
	}
	return '\0';
}

uint8_t I2C1_Master_Receive(uint16_t addr)
{
	uint8_t data;
	
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_1);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressR(I2C_1, addr);
	}
	
	data = I2Cx_Read_From_DR(I2C_1);
	
	/* Disable ACK */
	I2Cx_ACK_Dis(I2C_1);
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_1);
	
	return data;
}

uint8_t I2C2_Master_Receive(uint16_t addr)
{
	uint8_t data;
	
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_2);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressR(I2C_2, addr);
	}
	
	data = I2Cx_Read_From_DR(I2C_2);
	
	/* Disable ACK */
	I2Cx_ACK_Dis(I2C_2);
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_2);
	
	return data;
}

uint8_t I2C3_Master_Receive(uint16_t addr)
{
	uint8_t data;
	
	/* Generate START condition */
	I2Cx_GenerateSTART(I2C_3);
	
	/* Send slave address */
	if (addr > 0x7F) {
		//10-bit addressing mode
	}
	else {
		I2Cx_Send7bitAddressR(I2C_3, addr);
	}
	
	data = I2Cx_Read_From_DR(I2C_3);
	
	/* Disable ACK */
	I2Cx_ACK_Dis(I2C_3);
	
	/* Generate STOP condition */
	I2Cx_GenerateStop(I2C_3);
	
	return data;
}

uint8_t I2Cx_Master_Receive(I2Cx n, uint16_t addr)
{
	switch (n) {
		case I2C_1: return I2C1_Master_Receive(addr);
		case I2C_2: return I2C2_Master_Receive(addr);
		case I2C_3: return I2C3_Master_Receive(addr);
	}
	return '\0';
}

uint8_t I2C1_Slave_Receive()
{
}

uint8_t I2C2_Slave_Receive()
{
}

uint8_t I2C3_Slave_Receive()
{
}
