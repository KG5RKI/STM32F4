#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_spi.h"

#include "stdbool.h"

/* Define GPIO macros */
#define INPUT  0x0
#define OUTPUT 0x1
#define AF     0x2
#define ANALOG 0x3

#define PUSH_PULL  0x0
#define OPEN_DRAIN 0x1

#define LOW_SPEED       0x0
#define MEDIUM_SPEED    0x1
#define HIGH_SPEED      0x2
#define VERY_HIGH_SPEED 0x3

#define NO_PULL   0x0
#define PULL_UP   0x1
#define PULL_DOWN 0x2

#define AF5 0x5
#define AF6 0x6

void SPI1_GPIO_Init()
{
	/* SCK - PA5, MISO - PA6, MOSI - PA7 */
	RCC->AHB1ENR |= (1<<0);
	
	GPIOA->MODER |= (AF<<10);
	GPIOA->MODER |= (AF<<12);
	GPIOA->MODER |= (AF<<14);
	
	GPIOA->OTYPER &= ~(1<<5);
	GPIOA->OTYPER &= ~(1<<6);
	GPIOA->OTYPER &= ~(1<<7);
	
	GPIOA->OSPEEDR |= (VERY_HIGH_SPEED<<10);
	GPIOA->OSPEEDR |= (VERY_HIGH_SPEED<<12);
	GPIOA->OSPEEDR |= (VERY_HIGH_SPEED<<14);
	
	GPIOA->PUPDR &= ~(3<<10);
	GPIOA->PUPDR &= ~(3<<12);
	GPIOA->PUPDR &= ~(3<<14);
	
	GPIOA->AFR[0] |= (AF5<<20);
	GPIOA->AFR[0] |= (AF5<<24);
	GPIOA->AFR[0] |= (AF5<<28);
}

void SPI2_GPIO_Init()
{
	/* SCK - PB10, MISO - PC2, MOSI - PC3 */
	RCC->AHB1ENR |= (1<<1);
	RCC->AHB1ENR |= (1<<2);
	
	GPIOB->MODER |= (AF<<20);
	GPIOC->MODER |= (AF<<4);
	GPIOC->MODER |= (AF<<6);
	
	GPIOB->OTYPER &= ~(1<<10);
	GPIOC->OTYPER &= ~(1<<2);
	GPIOC->OTYPER &= ~(1<<3);
	
	GPIOB->OSPEEDR |= (VERY_HIGH_SPEED<<20);
	GPIOC->OSPEEDR |= (VERY_HIGH_SPEED<<4);
	GPIOC->OSPEEDR |= (VERY_HIGH_SPEED<<6);
	
	GPIOB->PUPDR &= ~(1<<20);
	GPIOC->PUPDR &= ~(1<<4);
	GPIOC->PUPDR &= ~(1<<6);
	
	GPIOB->AFR[1] |= (AF5<<8);
	GPIOC->AFR[0] |= (AF5<<8);
	GPIOC->AFR[0] |= (AF5<<12);
}

void SPI3_GPIO_Init()
{
	/* SCK - PC10, MISO - PC11, MOSI - PC12 */
	RCC->AHB1ENR |= (1<<2);
	
	GPIOC->MODER |= (AF<<20);
	GPIOC->MODER |= (AF<<22);
	GPIOC->MODER |= (AF<<24);
	
	GPIOC->OTYPER &= ~(1<<10);
	GPIOC->OTYPER &= ~(1<<11);
	GPIOC->OTYPER &= ~(1<<12);
	
	GPIOC->OSPEEDR |= (VERY_HIGH_SPEED<<20);
	GPIOC->OSPEEDR |= (VERY_HIGH_SPEED<<22);
	GPIOC->OSPEEDR |= (VERY_HIGH_SPEED<<24);
	
	GPIOC->PUPDR &= ~(0x3<<20);
	GPIOC->PUPDR &= ~(0x3<<22);
	GPIOC->PUPDR &= ~(0x3<<24);
	
	GPIOC->AFR[1] |= (AF6<<8);
	GPIOC->AFR[1] |= (AF6<<12);
	GPIOC->AFR[1] |= (AF6<<16);
}

uint8_t getBR(uint16_t prescalar)
{
	if (prescalar == 4)
		return 1;
	else if (prescalar == 8)
		return 2;
	else if (prescalar == 16)
		return 3;
	else if (prescalar == 32)
		return 4;
  else if (prescalar == 64)
		return 5;
  else if (prescalar == 128)
		return 6;
  else if (prescalar == 256)
		return 7;
	else return 0;
}

void SPI1_Init(SPI_Mode m, uint8_t dataframe, _Bool CPOL, _Bool CPHA, uint16_t prescalar)
{
	/* Enable SPI1 clock */
	RCC->APB2ENR |= (1<<12);
	
	/* Configure SPI1 mode */
	switch (m) {
		
		case FULL_DUPLEX_MASTER:
			SPI1->CR1 |= (1<<2); //Master
			SPI1->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case FULL_DUPLEX_SLAVE:
			SPI1->CR1 &= ~(1<<2); //Slave
			SPI1->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case HALF_DUPLEX_MASTER:
			SPI1->CR1 |= (1<<2); //Master
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 |= (1<<14); //Transmit-only
			break;
		
		case HALF_DUPLEX_SLAVE:
			SPI1->CR1 &= ~(1<<2); //Slave
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_MASTER:
			SPI1->CR1 |= (1<<2); //Master
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_SLAVE:
			SPI1->CR1 &= ~(1<<2); //Slave
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case TRANSMIT_ONLY_MASTER:
			SPI1->CR1 |= (1<<2); //Master
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 |= (1<<14); //Transmit-only
			break;
		
		case TRANSMIT_ONLY_SLAVE:
			SPI1->CR1 &= ~(1<<2); //Slave
			SPI1->CR1 |= (1<<15); //Bidirectional
			SPI1->CR1 |= (1<<14); //Transmit-only
			break;
	}
	
	/* Set data frame format - 8bit/16bit */
	if (dataframe == 16)
		SPI1->CR1 |= (1<<11);
	else
		SPI1->CR1 &= ~(1<<11);
	
	/* Set SPI baud rate */
	SPI1->CR1 |= (getBR(prescalar)<<3);
	
	/* Set clock polarity */
	SPI1->CR1 |= (CPOL<<1);
	
	/* Set clock phase */
	SPI1->CR1 |= (CPHA<<0);
	
	/* Intialize GPIO pins for SPI1 */
	SPI1_GPIO_Init();
}

void SPI2_Init(SPI_Mode m, uint8_t dataframe, _Bool CPOL, _Bool CPHA, uint16_t prescalar)
{
	/* Enable SPI2 clock */
	RCC->APB1ENR |= (1<<14);
	
	/* Configure SPI2 mode */
	switch (m) {
		
		case FULL_DUPLEX_MASTER:
			SPI2->CR1 |= (1<<2); //Master
			SPI2->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case FULL_DUPLEX_SLAVE:
			SPI2->CR1 &= ~(1<<2); //Slave
			SPI2->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case HALF_DUPLEX_MASTER:
			SPI2->CR1 |= (1<<2); //Master
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 |= (1<<14); //Transmit-only
			break;
		
		case HALF_DUPLEX_SLAVE:
			SPI2->CR1 &= ~(1<<2); //Slave
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_MASTER:
			SPI2->CR1 |= (1<<2); //Master
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_SLAVE:
			SPI2->CR1 &= ~(1<<2); //Slave
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case TRANSMIT_ONLY_MASTER:
			SPI2->CR1 |= (1<<2); //Master
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 |= (1<<14); //Transmit-only
			break;
		
		case TRANSMIT_ONLY_SLAVE:
			SPI2->CR1 &= ~(1<<2); //Slave
			SPI2->CR1 |= (1<<15); //Bidirectional
			SPI2->CR1 |= (1<<14); //Transmit-only
			break;
	}
	
	/* Set data frame format - 8bit/16bit */
	if (dataframe == 16)
		SPI2->CR1 |= (1<<11);
	else
		SPI2->CR1 &= ~(1<<11);
	
	/* Set SPI baud rate */
	SPI2->CR1 |= (getBR(prescalar)<<3);
	
	/* Set clock polarity */
	SPI2->CR1 |= (CPOL<<1);
	
	/* Set clock phase */
	SPI2->CR1 |= (CPHA<<0);
	
	/* Intialize GPIO pins for SPI2 */
	SPI2_GPIO_Init();
}

void SPI3_Init(SPI_Mode m, uint8_t dataframe, _Bool CPOL, _Bool CPHA, uint16_t prescalar)
{
	/* Enable SPI3 clock */
	RCC->APB1ENR |= (1<<15);
	
	/* Configure SPI3 mode */
	switch (m) {
		
		case FULL_DUPLEX_MASTER:
			SPI3->CR1 |= (1<<2); //Master
			SPI3->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case FULL_DUPLEX_SLAVE:
			SPI3->CR1 &= ~(1<<2); //Slave
			SPI3->CR1 &= ~(1<<15); //Unidirectional
			break;
		
		case HALF_DUPLEX_MASTER:
			SPI3->CR1 |= (1<<2); //Master
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 |= (1<<14); //Transmit-only
			break;
		
		case HALF_DUPLEX_SLAVE:
			SPI3->CR1 &= ~(1<<2); //Slave
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_MASTER:
			SPI3->CR1 |= (1<<2); //Master
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case RECEIVE_ONLY_SLAVE:
			SPI3->CR1 &= ~(1<<2); //Slave
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 &= ~(1<<14); //Receive-only
			break;
		
		case TRANSMIT_ONLY_MASTER:
			SPI3->CR1 |= (1<<2); //Master
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 |= (1<<14); //Transmit-only
			break;
		
		case TRANSMIT_ONLY_SLAVE:
			SPI3->CR1 &= ~(1<<2); //Slave
			SPI3->CR1 |= (1<<15); //Bidirectional
			SPI3->CR1 |= (1<<14); //Transmit-only
			break;
	}
	
	/* Set data frame format - 8bit/16bit */
	if (dataframe == 16)
		SPI3->CR1 |= (1<<11);
	else
		SPI3->CR1 &= ~(1<<11);
	
	/* Set SPI baud rate */
	SPI3->CR1 |= (getBR(prescalar)<<3);
	
	/* Set clock polarity */
	SPI3->CR1 |= (CPOL<<1);
	
	/* Set clock phase */
	SPI3->CR1 |= (CPHA<<0);
	
	/* Intialize GPIO pins for SPI3 */
	SPI3_GPIO_Init();
}

void SPIx_Init(SPIx n, SPI_Mode m, uint8_t dataframe,  _Bool CPOL, _Bool CPHA, uint16_t prescalar)
{
	switch (n) {
		case SPI_1: SPI1_Init(m, dataframe, CPOL, CPHA, prescalar); break;
		case SPI_2: SPI2_Init(m, dataframe, CPOL, CPHA, prescalar); break;
		case SPI_3: SPI3_Init(m, dataframe, CPOL, CPHA, prescalar); break;
	}
}

void SPI1_En()
{
	SPI1->CR1 |= (1<<6);
}

void SPI2_En()
{
	SPI2->CR1 |= (1<<6);
}

void SPI3_En()
{
	SPI3->CR1 |= (1<<6);
}

void SPIx_En(SPIx n)
{
	switch (n) {
		case SPI_1: SPI1_En(); break;
		case SPI_2: SPI2_En(); break;
		case SPI_3: SPI3_En(); break;
	}
}

void SPI1_Dis()
{
	SPI1->CR1 &= ~(1<<6);
}

void SPI2_Dis()
{
	SPI2->CR1 &= ~(1<<6);
}

void SPI3_Dis()
{
	SPI3->CR1 &= ~(1<<6);
}

void SPIx_Dis(SPIx n)
{
	switch (n) {
		case SPI_1: SPI1_Dis(); break;
		case SPI_2: SPI2_Dis(); break;
		case SPI_3: SPI3_Dis(); break;
	}
}

_Bool SPI1_RxBufferNotEmpty()
{
	return SPI1->SR & 0x1;
}

_Bool SPI2_RxBufferNotEmpty()
{
	return SPI2->SR & 0x1;
}

_Bool SPI3_RxBufferNotEmpty()
{
	return SPI3->SR & 0x1;
}

_Bool SPI1_TxBufferEmpty()
{
	return (SPI1->SR>>1) & 0x1;
}

_Bool SPI2_TxBufferEmpty()
{
	return (SPI2->SR>>1) & 0x1;
}

_Bool SPI3_TxBufferEmpty()
{
	return (SPI3->SR>>1) & 0x1;
}

_Bool SPI1_isBUSY()
{
	return (SPI1->SR>>7) & 0x1;
}

_Bool SPI2_isBusy()
{
	return (SPI2->SR>>7) & 0x1;
}

_Bool SPI3_isBusy()
{
	return (SPI3->SR>>7) & 0x1;
}

void SPI1_Send_8bits(uint8_t data)
{
	/* Send data */
	SPI1 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI1_TxBufferEmpty());
}

void SPI1_Send_16bits(uint16_t data)
{
	/* Send data */
	SPI1 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI1_TxBufferEmpty());
}

void SPI2_Send_8bits(uint8_t data)
{
	/* Send data */
	SPI2 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI2_TxBufferEmpty());
}

void SPI2_Send_16bits(uint16_t data)
{
	/* Send data */
	SPI2 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI2_TxBufferEmpty());
}

void SPI3_Send_8bits(uint8_t data)
{
	/* Send data */
	SPI3 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI3_TxBufferEmpty());
}

void SPI3_Send_16bits(uint16_t data)
{
	/* Send data */
	SPI3 -> DR = data;
	
	/* Wait until transmission is completed */
	while (!SPI3_TxBufferEmpty());
}

void SPIx_Send_8bits(SPIx n, uint8_t data)
{
	switch (n) {
		case SPI_1: SPI1_Send_8bits(data); break;
		case SPI_2: SPI2_Send_8bits(data); break;
		case SPI_3: SPI3_Send_8bits(data); break;
	}
}

void SPIx_Send_16bits(SPIx n, uint16_t data)
{
	switch (n) {
		case SPI_1: SPI1_Send_16bits(data); break;
		case SPI_2: SPI2_Send_16bits(data); break;
		case SPI_3: SPI3_Send_16bits(data); break;
	}
}

uint8_t SPI1_Receive_8bits()
{
	/* Wait until data is received */
	while (!SPI1_RxBufferNotEmpty());
	
	uint8_t data = SPI1 -> DR;
	return data;
}

uint8_t SPI1_Receive_16bits()
{
	/* Wait until data is received */
	while (!SPI1_RxBufferNotEmpty());
	
	uint16_t data = SPI1 -> DR;
	return data;
}

uint8_t SPI2_Receive_8bits()
{
	/* Wait until data is received */
	while (!SPI2_RxBufferNotEmpty());
	
	uint8_t data = SPI2 -> DR;
	return data;
}

uint8_t SPI2_Receive_16bits()
{
	/* Wait until data is received */
	while (!SPI2_RxBufferNotEmpty());
	
	uint16_t data = SPI2 -> DR;
	return data;
}

uint8_t SPI3_Receive_8bits()
{
	/* Wait until data is received */
	while (!SPI3_RxBufferNotEmpty());
	
	uint8_t data = SPI3 -> DR;
	return data;
}

uint8_t SPI3_Receive_16bits()
{
	/* Wait until data is received */
	while (!SPI3_RxBufferNotEmpty());
	
	uint16_t data = SPI3 -> DR;
	return data;
}

uint8_t SPIx_Receive_8bits(SPIx n)
{
	uint8_t data;
	switch (n) {
		case SPI_1: data = SPI1_Receive_8bits(); break;
		case SPI_2: data = SPI2_Receive_8bits(); break;
		case SPI_3: data = SPI3_Receive_8bits(); break;
	}
	return data;
}

uint16_t SPIx_Receive_16bits(SPIx n)
{
	uint16_t data;
	switch (n) {
		case SPI_1: data = SPI1_Receive_16bits(); break;
		case SPI_2: data = SPI2_Receive_16bits(); break;
		case SPI_3: data = SPI3_Receive_16bits(); break;
	}
	return data;
}

void SPI1_Interrupt_En(SPI_Interrupt_Event ei)
{
	switch (ei) {
		case TXE:    SPI1->CR2 |= (1<<7); break;
		case RXNE:   SPI1->CR2 |= (1<<6); break;
		case MODF:   SPI1->CR2 |= (1<<5); break;
		case OVR:    SPI1->CR2 |= (1<<5); break;
		case CRCERR: SPI1->CR2 |= (1<<5); break;
		case FRE:    SPI1->CR2 |= (1<<5); break;
	}
}

void SPI2_Interrupt_En(SPI_Interrupt_Event ei)
{
	switch (ei) {
		case TXE:    SPI2->CR2 |= (1<<7); break;
		case RXNE:   SPI2->CR2 |= (1<<6); break;
		case MODF:   SPI2->CR2 |= (1<<5); break;
		case OVR:    SPI2->CR2 |= (1<<5); break;
		case CRCERR: SPI2->CR2 |= (1<<5); break;
		case FRE:    SPI2->CR2 |= (1<<5); break;
	}
}

void SPI3_Interrupt_En(SPI_Interrupt_Event ei)
{
	switch (ei) {
		case TXE:    SPI3->CR2 |= (1<<7); break;
		case RXNE:   SPI3->CR2 |= (1<<6); break;
		case MODF:   SPI3->CR2 |= (1<<5); break;
		case OVR:    SPI3->CR2 |= (1<<5); break;
		case CRCERR: SPI3->CR2 |= (1<<5); break;
		case FRE:    SPI3->CR2 |= (1<<5); break;
	}
}

void SPIx_Interrupt_en(SPIx n, SPI_Interrupt_Event ei)
{
	switch (n) {
		case SPI_1: SPI1_Interrupt_En(ei);
		case SPI_2: SPI2_Interrupt_En(ei);
		case SPI_3: SPI3_Interrupt_En(ei);
	}
}
