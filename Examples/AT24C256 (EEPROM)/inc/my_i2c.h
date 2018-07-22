#include "stdint.h"

#define EEPROM_256K_ADDR 0x50

void I2C1_GPIO_Init(void);
void I2C1_Init(void);
void I2C1_SoftwareReset(void);
void I2C1_ACK_En(void);
void I2C1_ACK_Dis(void);
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

void EEPROM_256K_I2C1_Byte_Write(uint8_t, uint16_t, uint8_t);
void EEPROM_256K_I2C1_64Byte_Page_Write(uint8_t, uint8_t *);
uint8_t EEPROM_256K_I2C1_Current_Read(uint8_t);
uint8_t EEPROM_256K_I2C1_Random_Read(uint8_t, uint16_t);
void EEPROM_256K_I2C1_Sequential_Read(uint8_t, uint16_t, uint8_t *, int);
