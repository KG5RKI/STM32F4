#define GPIO_MODE_INPUT 0x0
#define GPIO_MODE_OUTPUT 0x1
#define GPIO_MODE_AF 0x2
#define GPIO_MODE_ANALOG 0x3

#define GPIO_OTYPE_PP 0x0
#define GPIO_OTYPE_OD 0x1

#define GPIO_SPEED_LOW 0x0
#define GPIO_SPEED_MEDIUM 0x1
#define GPIO_SPEED_HIGH 0x2
#define GPIO_SPEED_VERY_HIGH 0x3

#define GPIO_NO_PULL 0x0
#define GPIO_PULL_UP 0x1
#define GPIO_PULL_DOWN 0x2

#include "stm32f411xe.h"

void GPIO_SetPin(GPIO_TypeDef *, uint8_t);
void GPIO_ResetPin(GPIO_TypeDef *, uint8_t);
void GPIO_TogglePin(GPIO_TypeDef *, uint8_t);
void GPIO_Toggle2_With_Delay(GPIO_TypeDef *, uint8_t);
