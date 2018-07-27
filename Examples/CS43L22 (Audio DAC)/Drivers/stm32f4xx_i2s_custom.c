#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_gpio_custom.h"
#include "stm32f4xx_i2s_custom.h"

void I2S3_GPIO_Init()
{
	/* Configure I2S pins - WS(PA4), MCK(PC7), SCK(PC10) & SD(PC12) */
	GPIO_ClockInit(GPIOA);
	GPIO_ClockInit(GPIOC);
	GPIO_Config(GPIOA, 4, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PP, GPIO_OTYPE_PP, GPIO_PULL_UP);
	GPIO_Config(GPIOC, 7, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PP, GPIO_OTYPE_PP, GPIO_PULL_UP);
	GPIO_Config(GPIOC, 10, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PP, GPIO_OTYPE_PP, GPIO_PULL_UP);
	GPIO_Config(GPIOC, 12, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PP, GPIO_OTYPE_PP, GPIO_PULL_UP);
	GPIO_Config_AF(GPIOA, 4, GPIO_AF6);
	GPIO_Config_AF(GPIOC, 7, GPIO_AF6);
	GPIO_Config_AF(GPIOC, 10, GPIO_AF6);
	GPIO_Config_AF(GPIOC, 12, GPIO_AF6);
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
	
	SPI3->I2SPR |= (1 << 9);
	SPI3->I2SCFGR = 0xE1B;
}

void I2S3_SendData(uint16_t data)
{
	while (!((SPI3->SR >> 1) & 0x1));	//Wait until Tx buffer empty
	SPI3->DR = data;
}
