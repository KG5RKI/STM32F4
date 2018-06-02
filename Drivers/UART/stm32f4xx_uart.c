#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_uart.h"
#include "stdbool.h"
#include "stdint.h"

void UART1_GPIO_Init()
{
	/* Tx - PA9, Rx - PA10 */
	
	/* Enable GPIOA clock */
	RCC -> AHB1ENR |= (1<<0);
	
	/* Set pin mode to AF */
	GPIOA -> MODER |= (2<<18);
	GPIOA -> MODER |= (2<<20);
	
	/* Set speed to HIGH */
	GPIOA -> OSPEEDR |= (2<<18);
	GPIOA -> OSPEEDR |= (2<<20);
	
	/* Enable pull-up resistors */
	GPIOA -> PUPDR |= (1<<18);
	GPIOA -> PUPDR |= (1<<20);
}

void UART2_GPIO_Init()
{
	/* Tx - PA2, Rx - PA3 */
	
	/* Enable GPIOA clock */
	RCC -> AHB1ENR |= (1<<0);
	
	/* Set pin mode to AF */
	GPIOA -> MODER |= (2<<4);
	GPIOA -> MODER |= (2<<6);
	
	/* Set speed to HIGH */
	GPIOA -> OSPEEDR |= (2<<4);
	GPIOA -> OSPEEDR |= (2<<6);
	
	/* Enable pull-up resistors */
	GPIOA -> PUPDR |= (1<<4);
	GPIOA -> PUPDR |= (1<<6);
}

void UART3_GPIO_Init()
{
	/* Tx - PB10, Rx - PB11 */
	
	/* Enable GPIOB clock */
	RCC -> AHB1ENR |= (1<<1);
	
	/* Set pin mode to AF */
	GPIOB -> MODER |= (2<<20);
	GPIOB -> MODER |= (2<<22);
	
	/* Set speed to HIGH */
	GPIOB -> OSPEEDR |= (2<<20);
	GPIOB -> OSPEEDR |= (2<<22);
	
	/* Enable pull-up resistors */
	GPIOB -> PUPDR |= (1<<20);
	GPIOB -> PUPDR |= (1<<22);
}

void UART4_GPIO_Init()
{
	/* Tx - PA0, Rx - PA1 */
	
	/* Enable GPIOA clock */
	RCC -> AHB1ENR |= (1<<0);
	
	/* Set pin mode to AF */
	GPIOA -> MODER |= (2<<0);
	GPIOA -> MODER |= (2<<2);
	
	/* Set speed to HIGH */
	GPIOA -> OSPEEDR |= (2<<0);
	GPIOA -> OSPEEDR |= (2<<2);
	
	/* Enable pull-up resistors */
	GPIOA -> PUPDR |= (1<<0);
	GPIOA -> PUPDR |= (1<<2);
}

void UART5_GPIO_Init()
{
	/* Tx - PC12, Rx - PD2 */
	
	/* Enable GPIOC & GPIOD clock */
	RCC -> AHB1ENR |= (1<<2);
	RCC -> AHB1ENR |= (1<<3);
	
	/* Set pin mode to AF */
	GPIOC -> MODER |= (2<<24);
	GPIOD -> MODER |= (2<<4);
	
	/* Set speed to HIGH */
	GPIOC -> OSPEEDR |= (2<<24);
	GPIOD -> OSPEEDR |= (2<<4);
	
	/* Enable pull-up resistors */
	GPIOC -> PUPDR |= (1<<24);
	GPIOD -> PUPDR |= (1<<4);
}

void UART6_GPIO_Init()
{
	/* Tx - PC6, Rx - PC7 */
	
	/* Enable GPIOC clock */
	RCC -> AHB1ENR |= (1<<2);
	
	/* Set pin mode to AF */
	GPIOC -> MODER |= (2<<12);
	GPIOC -> MODER |= (2<<14);
	
	/* Set speed to HIGH */
	GPIOC -> OSPEEDR |= (2<<12);
	GPIOC -> OSPEEDR |= (2<<14);
	
	/* Enable pull-up resistors */
	GPIOC -> PUPDR |= (1<<12);
	GPIOC -> PUPDR |= (1<<14);
}

void UARTx_GPIO_Init(UARTx n)
{
	switch (n) {
		case UART_1: UART1_GPIO_Init(); break;
		case UART_2: UART2_GPIO_Init(); break;
		case UART_3: UART3_GPIO_Init(); break;
		case UART_4: UART4_GPIO_Init(); break;
		case UART_5: UART5_GPIO_Init(); break;
		case UART_6: UART6_GPIO_Init(); break;
	}
}

uint16_t getUSARTDIV(uint32_t baud_rate)
{
	if (baud_rate == 1200) {
		return 0x3415;
	}
	else if (baud_rate == 2400) {
		return 0x1A0B;
	}
	else if (baud_rate == 4800) {
		return 0xD05;
	}
	else if (baud_rate == 19200) {
		return 0x341;
	}
	else if (baud_rate == 38400) {
		return 0x1A1;
	}
	else if (baud_rate == 57600) {
		return 0x116;
	}
	else if (baud_rate == 115200) {
		return 0x8B;
	}
	else if (baud_rate == 230400) {
		return 0x45;
	}
	else {
		return 0x683;
	}
}

void UART1_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART1 clock */
	RCC -> APB2ENR |= (1<<4);
	
	/* Set UART1 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		USART1 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		USART1 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		USART1 -> CR2 &= ~(1<<13);
		USART1 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		USART1 -> CR2 |= (1<<13);
		USART1 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		USART1 -> CR2 |= (1<<13);
		USART1 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		USART1 -> CR2 &= ~(1<<13);
		USART1 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		USART1 -> CR3 |= (1<<0);
	}
	else {
		USART1 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	USART1 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART1 GPIO pins */
	UARTx_GPIO_Init(UART_1);
}

void UART2_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART2 clock */
	RCC -> APB1ENR |= (1<<17);
	
	/* Set UART2 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		USART2 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		USART2 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		USART2 -> CR2 &= ~(1<<13);
		USART2 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		USART2 -> CR2 |= (1<<13);
		USART2 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		USART2 -> CR2 |= (1<<13);
		USART2 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		USART2 -> CR2 &= ~(1<<13);
		USART2 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		USART2 -> CR3 |= (1<<0);
	}
	else {
		USART2 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	USART2 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART2 GPIO pins */
	UARTx_GPIO_Init(UART_2);
}

void UART3_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART3 clock */
	RCC -> APB1ENR |= (1<<18);
	
	/* Set UART3 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		USART3 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		USART3 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		USART3 -> CR2 &= ~(1<<13);
		USART3 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		USART3 -> CR2 |= (1<<13);
		USART3 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		USART3 -> CR2 |= (1<<13);
		USART3 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		USART3 -> CR2 &= ~(1<<13);
		USART3 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		USART3 -> CR3 |= (1<<0);
	}
	else {
		USART3 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	USART3 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART3 GPIO pins */
	UARTx_GPIO_Init(UART_3);
}

void UART4_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART4 clock */
	RCC -> APB1ENR |= (1<<19);
	
	/* Set UART4 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		UART4 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		UART4 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		UART4 -> CR2 &= ~(1<<13);
		UART4 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		UART4 -> CR2 |= (1<<13);
		UART4 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		UART4 -> CR2 |= (1<<13);
		UART4 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		UART4 -> CR2 &= ~(1<<13);
		UART4 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		UART4 -> CR3 |= (1<<0);
	}
	else {
		UART4 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	UART4 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART4 GPIO pins */
	UARTx_GPIO_Init(UART_4);
}

void UART5_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART5 clock */
	RCC -> APB1ENR |= (1<<20);
	
	/* Set UART5 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		UART5 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		UART5 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		UART5 -> CR2 &= ~(1<<13);
		UART5 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		UART5 -> CR2 |= (1<<13);
		UART5 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		UART5 -> CR2 |= (1<<13);
		UART5 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		UART5 -> CR2 &= ~(1<<13);
		UART5 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		UART5 -> CR3 |= (1<<0);
	}
	else {
		UART5 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	UART5 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART5 GPIO pins */
	UARTx_GPIO_Init(UART_5);
}

void UART6_Init(uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	/* Enable UART6 clock */
	RCC -> APB2ENR |= (1<<5);
	
	/* Set UART6 word length */
	if (data_bits == 9) {
		/* Word length = 9-bits */
		USART6 -> CR1 |= (1<<12);
	}
	else {
		/* Word length = 8-bits */
		USART6 -> CR1 |= (1<<12);
	}
	
	/* Set number of STOP bits */
	if (STOP == 0.5) {
		USART6 -> CR2 &= ~(1<<13);
		USART6 -> CR2 |= (1<<12);
	}
	else if (STOP == 2) {
		USART6 -> CR2 |= (1<<13);
		USART6 -> CR2 &= ~(1<<12);
	}
	else if (STOP == 1.5) {
		USART6 -> CR2 |= (1<<13);
		USART6 -> CR2 |= (1<<12);
	}
	else {
		/* STOP = 1 */
		USART6 -> CR2 &= ~(1<<13);
		USART6 -> CR2 &= ~(1<<12);
	}
	
	/* Select Half-duplex or Full-duplex mode*/
	if (HDSEL == 1) {
		USART6 -> CR3 |= (1<<0);
	}
	else {
		USART6 -> CR3 &= ~(1<<0);
	}
	
	/* Set the baud rate */
	USART6 -> BRR |= getUSARTDIV(baud_rate);
	
	/* Enable UART6 GPIO pins */
	UARTx_GPIO_Init(UART_6);
}

void UARTx_Init(UARTx n, uint8_t data_bits, double STOP, _Bool HDSEL, uint32_t baud_rate)
{
	switch (n) {
		case UART_1: UART1_Init(data_bits, STOP, HDSEL, baud_rate); break;
		case UART_2: UART2_Init(data_bits, STOP, HDSEL, baud_rate); break;
		case UART_3: UART3_Init(data_bits, STOP, HDSEL, baud_rate); break;
		case UART_4: UART4_Init(data_bits, STOP, HDSEL, baud_rate); break;
		case UART_5: UART5_Init(data_bits, STOP, HDSEL, baud_rate); break;
		case UART_6: UART6_Init(data_bits, STOP, HDSEL, baud_rate); break;
	}
}

void UART1_En()
{
	USART1 -> CR1 |= (1<<13);
}

void UART2_En()
{
	USART2 -> CR1 |= (1<<13);
}

void UART3_En()
{
	USART3 -> CR1 |= (1<<13);
}

void UART4_En()
{
	UART4 -> CR1 |= (1<<13);
}

void UART5_En()
{
	UART5 -> CR1 |= (1<<13);
}

void UART6_En()
{
	USART6 -> CR1 |= (1<<13);
}

void UARTx_En(UARTx n)
{
	switch (n) {
		case UART_1: UART1_En(); break;
		case UART_2: UART2_En(); break;
		case UART_3: UART3_En(); break;
		case UART_4: UART4_En(); break;
		case UART_5: UART5_En(); break;
		case UART_6: UART6_En(); break;
	}
}

void UART1_Dis()
{
	USART1 -> CR1 &= ~(1<<13);
}

void UART2_Dis()
{
	USART2 -> CR1 &= ~(1<<13);
}

void UART3_Dis()
{
	USART3 -> CR1 &= ~(1<<13);
}

void UART4_Dis()
{
	UART4 -> CR1 &= ~(1<<13);
}

void UART5_Dis()
{
	UART5 -> CR1 &= ~(1<<13);
}

void UART6_Dis()
{
	USART6 -> CR1 &= ~(1<<13);
}

void UARTx_Dis(UARTx n)
{
	switch (n) {
		case UART_1: UART1_Dis(); break;
		case UART_2: UART2_Dis(); break;
		case UART_3: UART3_Dis(); break;
		case UART_4: UART4_Dis(); break;
		case UART_5: UART5_Dis(); break;
		case UART_6: UART6_Dis(); break;
	}
}

void UART1_Tx_En()
{
	USART1 -> CR1 |= (1<<3);
}

void UART2_Tx_En()
{
	USART2 -> CR1 |= (1<<3);
}

void UART3_Tx_En()
{
	USART3 -> CR1 |= (1<<3);
}

void UART4_Tx_En()
{
	UART4 -> CR1 |= (1<<3);
}

void UART5_Tx_En()
{
	UART5 -> CR1 |= (1<<3);
}

void UART6_Tx_En()
{
	USART6 -> CR1 |= (1<<3);
}

void UARTx_Tx_En(UARTx n)
{
	switch (n) {
		case UART_1: UART1_Tx_En(); break;
		case UART_2: UART2_Tx_En(); break;
		case UART_3: UART3_Tx_En(); break;
		case UART_4: UART4_Tx_En(); break;
		case UART_5: UART5_Tx_En(); break;
		case UART_6: UART6_Tx_En(); break;
	}
}

void UART1_Tx_Dis()
{
	USART1 -> CR1 &= ~(1<<3);
}

void UART2_Tx_Dis()
{
	USART2 -> CR1 &= ~(1<<3);
}

void UART3_Tx_Dis()
{
	USART3 -> CR1 &= ~(1<<3);
}

void UART4_Tx_Dis()
{
	UART4 -> CR1 &= ~(1<<3);
}

void UART5_Tx_Dis()
{
	UART5 -> CR1 &= ~(1<<3);
}

void UART6_Tx_Dis()
{
	USART6 -> CR1 &= ~(1<<3);
}

void UARTx_Tx_Dis(UARTx n)
{
	switch (n) {
		case UART_1: UART1_Tx_Dis(); break;
		case UART_2: UART2_Tx_Dis(); break;
		case UART_3: UART3_Tx_Dis(); break;
		case UART_4: UART4_Tx_Dis(); break;
		case UART_5: UART5_Tx_Dis(); break;
		case UART_6: UART6_Tx_Dis(); break;
	}
}

void UART1_Rx_En()
{
	USART1 -> CR1 |= (1<<2);
}

void UART2_Rx_En()
{
	USART2 -> CR1 |= (1<<2);
}

void UART3_Rx_En()
{
	USART3 -> CR1 |= (1<<2);
}

void UART4_Rx_En()
{
	UART4 -> CR1 |= (1<<2);
}

void UART5_Rx_En()
{
	UART5 -> CR1 |= (1<<2);
}

void UART6_Rx_En()
{
	USART6 -> CR1 |= (1<<2);
}

void UARTx_Rx_En(UARTx n)
{
	switch (n) {
		case UART_1: UART1_Rx_En(); break;
		case UART_2: UART2_Rx_En(); break;
		case UART_3: UART3_Rx_En(); break;
		case UART_4: UART4_Rx_En(); break;
		case UART_5: UART5_Rx_En(); break;
		case UART_6: UART6_Rx_En(); break;
	}
}

void UART1_Rx_Dis()
{
	USART1 -> CR1 &= ~(1<<2);
}

void UART2_Rx_Dis()
{
	USART2 -> CR1 &= ~(1<<2);
}

void UART3_Rx_Dis()
{
	USART3 -> CR1 &= ~(1<<2);
}

void UART4_Rx_Dis()
{
	UART4 -> CR1 &= ~(1<<2);
}

void UART5_Rx_Dis()
{
	UART5 -> CR1 &= ~(1<<2);
}

void UART6_Rx_Dis()
{
	USART6 -> CR1 &= ~(1<<2);
}

void UARTx_Rx_Dis(UARTx n)
{
	switch (n) {
		case UART_1: UART1_Rx_Dis(); break;
		case UART_2: UART2_Rx_Dis(); break;
		case UART_3: UART3_Rx_Dis(); break;
		case UART_4: UART4_Rx_Dis(); break;
		case UART_5: UART5_Rx_Dis(); break;
		case UART_6: UART6_Rx_Dis(); break;
	}
}

void UART1_waitUntilTxRegEmpty()
{
	while (!(USART1 -> SR >> 7 & 0x01));
}

void UART2_waitUntilTxRegEmpty()
{
	while (!(USART2 -> SR >> 7 & 0x01));
}

void UART3_waitUntilTxRegEmpty()
{
	while (!(USART3 -> SR >> 7 & 0x01));
}

void UART4_waitUntilTxRegEmpty()
{
	while (!(UART4 -> SR >> 7 & 0x01));
}

void UART5_waitUntilTxRegEmpty()
{
	while (!(UART5 -> SR >> 7 & 0x01));
}

void UART6_waitUntilTxRegEmpty()
{
	while (!(USART6 -> SR >> 7 & 0x01));
}

void UARTx_waitUntilTxRegEmpty(UARTx n)
{
	switch (n) {
		case UART_1: UART1_waitUntilTxRegEmpty(); break;
		case UART_2: UART2_waitUntilTxRegEmpty(); break;
		case UART_3: UART3_waitUntilTxRegEmpty(); break;
		case UART_4: UART4_waitUntilTxRegEmpty(); break;
		case UART_5: UART5_waitUntilTxRegEmpty(); break;
		case UART_6: UART6_waitUntilTxRegEmpty(); break;
	}
}

void UART1_waitUntilRxDataAvailable()
{
	while (!(USART1 -> SR >> 5 & 0x01));
}

void UART2_waitUntilRxDataAvailable()
{
	while (!(USART2 -> SR >> 5 & 0x01));
}

void UART3_waitUntilRxDataAvailable()
{
	while (!(USART3 -> SR >> 5 & 0x01));
}

void UART4_waitUntilRxDataAvailable()
{
	while (!(UART4 -> SR >> 5 & 0x01));
}

void UART5_waitUntilRxDataAvailable()
{
	while (!(UART5 -> SR >> 5 & 0x01));
}

void UART6_waitUntilRxDataAvailable()
{
	while (!(USART6 -> SR >> 5 & 0x01));
}

void UARTx_waitUntilRxDataAvailable(UARTx n)
{
	switch (n) {
		case UART_1: UART1_waitUntilRxDataAvailable(); break;
		case UART_2: UART2_waitUntilRxDataAvailable(); break;
		case UART_3: UART3_waitUntilRxDataAvailable(); break;
		case UART_4: UART4_waitUntilRxDataAvailable(); break;
		case UART_5: UART5_waitUntilRxDataAvailable(); break;
		case UART_6: UART6_waitUntilRxDataAvailable(); break;
	}
}

void UART1_waitUntilTransmissionComplete()
{
	while (!((USART1 -> SR >> 6) & 0x01));
}

void UART2_waitUntilTransmissionComplete()
{
	while (!((USART2 -> SR >> 6) & 0x01));
}

void UART3_waitUntilTransmissionComplete()
{
	while (!((USART3 -> SR >> 6) & 0x01));
}

void UART4_waitUntilTransmissionComplete()
{
	while (!((UART4 -> SR >> 6) & 0x01));
}

void UART5_waitUntilTransmissionComplete()
{
	while (!((UART5 -> SR >> 6) & 0x01));
}

void UART6_waitUntilTransmissionComplete()
{
	while (!((USART6 -> SR >> 6) & 0x01));
}

void UARTx_waitUntilTransmissionComplete(UARTx n)
{
	switch (n) {
		case UART_1: UART1_waitUntilTransmissionComplete(); break;
		case UART_2: UART2_waitUntilTransmissionComplete(); break;
		case UART_3: UART3_waitUntilTransmissionComplete(); break;
		case UART_4: UART4_waitUntilTransmissionComplete(); break;
		case UART_5: UART5_waitUntilTransmissionComplete(); break;
		case UART_6: UART6_waitUntilTransmissionComplete(); break;
	}
}

void UART1_Tx_char(char ch)
{
	USART1 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_1);
}

void UART2_Tx_char(char ch)
{
	USART2 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_2);
}

void UART3_Tx_char(char ch)
{
	USART3 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_3);
}

void UART4_Tx_char(char ch)
{
	UART4 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_4);
}

void UART5_Tx_char(char ch)
{
	UART5 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_5);
}

void UART6_Tx_char(char ch)
{
	USART6 -> DR = ch;
	UARTx_waitUntilTxRegEmpty(UART_6);
}

void UARTx_Tx_char(UARTx n, char ch)
{
	switch (n) {
		case UART_1: UART1_Tx_char(ch); break;
		case UART_2: UART2_Tx_char(ch); break;
		case UART_3: UART3_Tx_char(ch); break;
		case UART_4: UART4_Tx_char(ch); break;
		case UART_5: UART5_Tx_char(ch); break;
		case UART_6: UART6_Tx_char(ch); break;
	}
}

void UART1_Tx_int(int i)
{
	UARTx_Tx_char(UART_1, (char)i+48);
}

void UART2_Tx_int(int i)
{
	UARTx_Tx_char(UART_2, (char)i+48);
}

void UART3_Tx_int(int i)
{
	UARTx_Tx_char(UART_3, (char)i+48);
}

void UART4_Tx_int(int i)
{
	UARTx_Tx_char(UART_4, (char)i+48);
}

void UART5_Tx_int(int i)
{
	UARTx_Tx_char(UART_5, (char)i+48);
}

void UART6_Tx_int(int i)
{
	UARTx_Tx_char(UART_6, (char)i+48);
}

void UARTx_Tx_int(UARTx n, int i)
{
	switch (n) {
		case UART_1: UART1_Tx_int(i); break;
		case UART_2: UART2_Tx_int(i); break;
		case UART_3: UART3_Tx_int(i); break;
		case UART_4: UART4_Tx_int(i); break;
		case UART_5: UART5_Tx_int(i); break;
		case UART_6: UART6_Tx_int(i); break;
	}
}

void UART1_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_1, *s);
		s++;
	}
}

void UART2_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_2, *s);
		s++;
	}
}

void UART3_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_3, *s);
		s++;
	}
}

void UART4_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_4, *s);
		s++;
	}
}

void UART5_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_5, *s);
		s++;
	}
}

void UART6_Tx_string(char *s)
{
	while (*s) {
		UARTx_Tx_char(UART_6, *s);
		s++;
	}
}

void UARTx_Tx_string(UARTx n, char *s)
{
	switch (n) {
		case UART_1: UART1_Tx_string(s); break;
		case UART_2: UART2_Tx_string(s); break;
		case UART_3: UART3_Tx_string(s); break;
		case UART_4: UART4_Tx_string(s); break;
		case UART_5: UART5_Tx_string(s); break;
		case UART_6: UART6_Tx_string(s); break;
	}
}

char UART1_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_1);
	readData = (char)USART1 -> DR;
	return readData;
}

char UART2_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_2);
	readData = (char)USART2 -> DR;
	return readData;
}

char UART3_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_3);
	readData = (char)USART3 -> DR;
	return readData;
}

char UART4_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_4);
	readData = (char)UART4 -> DR;
	return readData;
}

char UART5_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_5);
	readData = (char)UART5 -> DR;
	return readData;
}

char UART6_Rx_char() {
	char readData;
	UARTx_waitUntilRxDataAvailable(UART_6);
	readData = (char)USART6 -> DR;
	return readData;
}

char UARTx_Rx_char(UARTx n)
{
	switch (n) {
		case UART_1: return UART1_Rx_char();
		case UART_2: return UART2_Rx_char();
		case UART_3: return UART3_Rx_char();
		case UART_4: return UART4_Rx_char();
		case UART_5: return UART5_Rx_char();
		case UART_6: return UART6_Rx_char();
	}
	return '\0';
}

int UART1_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_1);
	readData = (int)(USART6 -> DR - 48);
	return readData;
}

int UART2_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_2);
	readData = (int)(USART2 -> DR - 48);
	return readData;
}

int UART3_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_3);
	readData = (int)(USART3 -> DR - 48);
	return readData;
}

int UART4_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_4);
	readData = (int)(UART4 -> DR - 48);
	return readData;
}

int UART5_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_5);
	readData = (int)(UART5 -> DR - 48);
	return readData;
}

int UART6_Rx_int() {
	int readData;
	UARTx_waitUntilRxDataAvailable(UART_6);
	readData = (int)(USART6 -> DR - 48);
	return readData;
}

int UARTx_Rx_int(UARTx n)
{
	switch (n) {
		case UART_1: return UART1_Rx_int();
		case UART_2: return UART2_Rx_int();
		case UART_3: return UART3_Rx_int();
		case UART_4: return UART4_Rx_int();
		case UART_5: return UART5_Rx_int();
		case UART_6: return UART6_Rx_int();
	}
	return 0;
}

void UART1_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_1);
		memloc++;
	}
}

void UART2_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_2);
		memloc++;
	}
}

void UART3_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_3);
		memloc++;
	}
}

void UART4_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_4);
		memloc++;
	}
}

void UART5_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_5);
		memloc++;
	}
}

void UART6_Rx_char_memwrite(char *memloc, int data_items)
{
	for (int i = 0; i < data_items; i++) {
		*memloc = UARTx_Rx_char(UART_6);
		memloc++;
	}
}

void UARTx_Rx_char_memwrite(UARTx n, char *memloc, int data_items)
{
	switch (n) {
		case UART_1: UART1_Rx_char_memwrite(memloc, data_items); break;
		case UART_2: UART2_Rx_char_memwrite(memloc, data_items); break;
		case UART_3: UART3_Rx_char_memwrite(memloc, data_items); break;
		case UART_4: UART4_Rx_char_memwrite(memloc, data_items); break;
		case UART_5: UART5_Rx_char_memwrite(memloc, data_items); break;
		case UART_6: UART6_Rx_char_memwrite(memloc, data_items); break;
	}
}

void UART1_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : USART1 -> CR1 |= (1<<7) ; break;
		case CTS      : USART1 -> CR3 |= (1<<10); break;
		case TC       : USART1 -> CR1 |= (1<<6) ; break;
		case RXNE     : USART1 -> CR1 |= (1<<5) ; break;
		case ORE      : USART1 -> CR1 |= (1<<5) ; break;
		case IDLE     : USART1 -> CR1 |= (1<<4) ; break;
		case PE       : USART1 -> CR1 |= (1<<8) ; break;
		case LBD      : USART1 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: USART1 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(USART1_IRQn);
}

void UART2_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : USART2 -> CR1 |= (1<<7) ; break;
		case CTS      : USART2 -> CR3 |= (1<<10); break;
		case TC       : USART2 -> CR1 |= (1<<6) ; break;
		case RXNE     : USART2 -> CR1 |= (1<<5) ; break;
		case ORE      : USART2 -> CR1 |= (1<<5) ; break;
		case IDLE     : USART2 -> CR1 |= (1<<4) ; break;
		case PE       : USART2 -> CR1 |= (1<<8) ; break;
		case LBD      : USART2 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: USART2 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(USART2_IRQn);
}

void UART3_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : USART3 -> CR1 |= (1<<7) ; break;
		case CTS      : USART3 -> CR3 |= (1<<10); break;
		case TC       : USART3 -> CR1 |= (1<<6) ; break;
		case RXNE     : USART3 -> CR1 |= (1<<5) ; break;
		case ORE      : USART3 -> CR1 |= (1<<5) ; break;
		case IDLE     : USART3 -> CR1 |= (1<<4) ; break;
		case PE       : USART3 -> CR1 |= (1<<8) ; break;
		case LBD      : USART3 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: USART3 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(USART3_IRQn);
}
	
void UART4_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : UART4 -> CR1 |= (1<<7) ; break;
		case CTS      : UART4 -> CR3 |= (1<<10); break;
		case TC       : UART4 -> CR1 |= (1<<6) ; break;
		case RXNE     : UART4 -> CR1 |= (1<<5) ; break;
		case ORE      : UART4 -> CR1 |= (1<<5) ; break;
		case IDLE     : UART4 -> CR1 |= (1<<4) ; break;
		case PE       : UART4 -> CR1 |= (1<<8) ; break;
		case LBD      : UART4 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: UART4 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(UART4_IRQn);
}

void UART5_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : UART5 -> CR1 |= (1<<7) ; break;
		case CTS      : UART5 -> CR3 |= (1<<10); break;
		case TC       : UART5 -> CR1 |= (1<<6) ; break;
		case RXNE     : UART5 -> CR1 |= (1<<5) ; break;
		case ORE      : UART5 -> CR1 |= (1<<5) ; break;
		case IDLE     : UART5 -> CR1 |= (1<<4) ; break;
		case PE       : UART5 -> CR1 |= (1<<8) ; break;
		case LBD      : UART5 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: UART5 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(UART5_IRQn);
}

void UART6_Interrupt_Event_En(USART_Interrupt_Event ie)
{
	switch (ie) {
		case TXE      : USART6 -> CR1 |= (1<<7) ; break;
		case CTS      : USART6 -> CR3 |= (1<<10); break;
		case TC       : USART6 -> CR1 |= (1<<6) ; break;
		case RXNE     : USART6 -> CR1 |= (1<<5) ; break;
		case ORE      : USART6 -> CR1 |= (1<<5) ; break;
		case IDLE     : USART6 -> CR1 |= (1<<4) ; break;
		case PE       : USART6 -> CR1 |= (1<<8) ; break;
		case LBD      : USART6 -> CR2 |= (1<<6) ; break;
		case NF_ORE_FE: USART6 -> CR3 |= (1<<0) ; break;
	}
	NVIC_EnableIRQ(USART6_IRQn);
}

void UARTx_Interrupt_Event_En(UARTx n, USART_Interrupt_Event ie)
{
	switch (n) {
		case UART_1: UART1_Interrupt_Event_En(ie); break;
		case UART_2: UART2_Interrupt_Event_En(ie); break;
		case UART_3: UART3_Interrupt_Event_En(ie); break;
		case UART_4: UART4_Interrupt_Event_En(ie); break;
		case UART_5: UART5_Interrupt_Event_En(ie); break;
		case UART_6: UART6_Interrupt_Event_En(ie); break;
	}
}
