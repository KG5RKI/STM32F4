#include "stdint.h"

void I2C1_GPIO_Init(void);
void I2C1_Init(void);
void I2C1_WaitUntilPeripheralFree(void);
void I2C1_WaitUntilTxRegEmpty(void);
void I2C1_WaitUntilRxRegNotEmpty(void);
void I2C1_WaitUntilBTF(void);
void I2C1_GenerateSTART(void);
void I2C1_Send7bitAddressW(uint8_t);
void I2C1_Send7bitAddressR(uint8_t);
void I2C1_GenerateStop(void);
void I2C1_Set_DR(uint8_t);
uint8_t I2C1_Get_DR(void);
void I2C1_Write(uint8_t, uint8_t, uint8_t);
uint8_t I2C1_Read(uint8_t, uint8_t);
