#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_i2s_custom.h"

void I2S3_GPIO_Init()
{
	/* Enable GPIOA & GPIOC clock */
	RCC->AHB1ENR |= (1<<0);
	RCC->AHB1ENR |= (1<<2);
	
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
}

void PLL_I2S_Clock_Configure()
{
	/* Enable PLLI2S clock */
	RCC->CR |= (1<<26);
	
	/* Wait until PLL I2S clock is locked */
	while (!((RCC->CR>>27) & 0x1));
	
	/* Set division factor for the PLLI2S clock, before VCO
	 * so that VCO input frequency ~ 1-2MHz
	 * HSI is 16MHz, so divide by 8
	 */
	RCC->PLLCFGR |= (1<<3);
	RCC->PLLCFGR &= ~(3<<4);
	
	/* Now PLLI2S is at 2MHz */
	
	/* Set PLLI2S division factor for I2C clock */
	RCC->PLLI2SCFGR |= (2<<28);
	
	/* Now PLLI2S is at 1MHz */
	
	/* Set PLLI2S multiplication factor for VCO */
	RCC->PLLI2SCFGR &= ~(0xF<<6);
	RCC->PLLI2SCFGR |= (3<<10);
	RCC->PLLI2SCFGR &= ~(3<<12);
	
	/* Now PLLI2S is at 48MHz */
	
	/* Set HSI as the PLLI2S clock source */
	RCC->PLLCFGR &= ~(1<<22);
	
	/* Set PLLI2S clock as the I2S clock */
	RCC->CFGR &= ~(1<<23);
	
	/* Enable I2S3 clock */
	RCC->APB1ENR |= (1<<15);
}

void I2S3_Init()
{
	I2S3_GPIO_Init();
	PLL_I2S_Clock_Configure();
	
	SPI3->I2SCFGR &= ~(1<<0);	//Channel length - 16bits
	SPI3->I2SCFGR &= ~(3<<1);	//Data length - 16bits
	SPI3->I2SCFGR &= ~(1<<3); //Clock polartiy low
	SPI3->I2SCFGR &= ~(3<<4); //I2S Philips standard
	SPI3->I2SCFGR |= (2<<8);  //I2S Mode - Master Tx
	SPI3->I2SCFGR |= (1<<11); //I2S mode selected
	SPI3->I2SPR |= (1<<9); 		//Master clock output enable 
	SPI3->I2SCFGR |= (1<<10); //I2S Enable
}

void I2S3_SendData(uint16_t data)
{
	while (!((SPI3->SR >> 1) & 0x1));	//Wait until Tx buffer empty
	SPI3->DR = data;
}
