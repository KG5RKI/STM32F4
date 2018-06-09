enum SPIx {SPI_1, SPI_2, SPI_3};
typedef enum SPIx SPIx;

enum SPI_Mode {
	FULL_DUPLEX_MASTER,
	FULL_DUPLEX_SLAVE,
	HALF_DUPLEX_MASTER,
	HALF_DUPLEX_SLAVE,
	RECEIVE_ONLY_MASTER,
	RECEIVE_ONLY_SLAVE,
	TRANSMIT_ONLY_MASTER,
	TRANSMIT_ONLY_SLAVE
};
typedef enum SPI_Mode SPI_Mode;

enum SPI_Interrupt_Event {TXE, RXNE, MODF, OVR, CRCERR, FRE };
typedef enum SPI_Interrupt_Event SPI_Interrupt_Event;

extern void SPIx_Init(SPIx, SPI_Mode, uint8_t, _Bool, _Bool, uint16_t);
extern void SPIx_En(SPIx);
extern void SPIx_Dis(SPIx);
extern void SPIx_Send_8bits(SPIx, uint8_t);
extern void SPIx_Send_16bits(SPIx, uint16_t);
extern uint8_t SPIx_Receive_8bits(SPIx);
extern uint16_t SPIx_Receive_16bits(SPIx);
extern void SPIx_Interrupt_en(SPIx n, SPI_Interrupt_Event);
