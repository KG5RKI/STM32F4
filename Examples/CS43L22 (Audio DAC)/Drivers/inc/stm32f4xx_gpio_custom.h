#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1
#define GPIO_MODE_ALTERNATE 2
#define GPIO_MODE_ANALOG 3

#define GPIO_OTYPE_PP 0
#define GPIO_OTYPE_OD 1

#define GPIO_OSPEED_LOW 0
#define GPIO_OSPEED_MEDIUM 1
#define GPIO_OSPEED_FAST 2
#define GPIO_OSPEED_HIGH 3

#define GPIO_NO_PULL 0
#define GPIO_PULL_UP 1
#define GPIO_PULL_DOWN 2

#define GPIO_AF0 0
#define GPIO_AF1 1
#define GPIO_AF2 2
#define GPIO_AF3 3
#define GPIO_AF4 4
#define GPIO_AF5 5
#define GPIO_AF6 6
#define GPIO_AF7 7
#define GPIO_AF8 8
#define GPIO_AF9 9
#define GPIO_AF10 10
#define GPIO_AF11 11
#define GPIO_AF12 12
#define GPIO_AF13 13
#define GPIO_AF14 14
#define GPIO_AF15 15

#include "stm32f411xe.h"

void GPIO_ClockInit(GPIO_TypeDef *);
void GPIO_Config(GPIO_TypeDef *, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void GPIO_Config_AF(GPIO_TypeDef *, uint8_t, uint8_t);
void GPIO_SetPin(GPIO_TypeDef *, uint8_t);
void GPIO_ResetPin(GPIO_TypeDef *, uint8_t);
