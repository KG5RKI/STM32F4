enum I2Cx {I2C_1, I2C_2, I2C_3};
typedef enum I2Cx I2Cx;

enum I2C_Mode {
	SLAVE_TRANSMITTER,
	SLAVE_RECEIVER,
	MASTER_TRANSMITTER,
	MASTER_RECEIVER
};
	
extern void I2Cx_Init(I2Cx);
extern void I2Cx_En(I2Cx);
extern void I2Cx_Dis(I2Cx);
