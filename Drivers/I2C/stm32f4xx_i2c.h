#include <stdint.h>

enum I2Cx {I2C_1, I2C_2, I2C_3};
typedef enum I2Cx I2Cx;

enum I2C_Mode {
	SLAVE_TRANSMITTER,
	SLAVE_RECEIVER,
	MASTER_TRANSMITTER,
	MASTER_RECEIVER
};

enum I2C_Interrupt {
	SB,			//Start bit sent
	ADDR,		//Address sent(master)/matched(slave)
	ADD10,	//10-bit header sent(slave)
	STOPF,	//Stop received(master)
	BTF,		//Byte transfer finished
	RxNE,		//Receive buffer not empty
	TxE,		//Transmit buffer empty
	BERR,		//Bus error
	ARLO,		//Arbitration loss(master)
	AF,			//Acknowledge failure
	OVR,		//Overrum/Underrun
	PECERR,	//PEC error
	TIMEOUT,//Timeout error
	SMBALERT//SMBus alert
};

typedef enum I2C_Interrupt I2C_Interrupt;
	
extern void I2Cx_Init(I2Cx, _Bool, uint8_t);
extern void I2Cx_En(I2Cx);
extern void I2Cx_Dis(I2Cx);
