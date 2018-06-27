#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GPIOA_BASE_ADDR (uint32_t)0x40020000
#define GPIOB_BASE_ADDR (uint32_t)0x40020400
#define GPIOC_BASE_ADDR (uint32_t)0x40020800
#define GPIOD_BASE_ADDR (uint32_t)0x40020C00
#define GPIOE_BASE_ADDR (uint32_t)0x40021000
#define GPIOF_BASE_ADDR (uint32_t)0x40021400
#define GPIOG_BASE_ADDR (uint32_t)0x40021800
#define GPIOH_BASE_ADDR (uint32_t)0x40021C00
#define GPIOI_BASE_ADDR (uint32_t)0x40022000
#define GPIOJ_BASE_ADDR (uint32_t)0x40022400
#define GPIOK_BASE_ADDR (uint32_t)0x40022800

struct GPIO {
    uint32_t MODER;
    uint16_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint16_t IDR;
    uint16_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFR[2];
};

typedef struct GPIO GPIO; 

int main(void) {
    GPIO *GPIOD = (GPIO *)GPIOD_BASE_ADDR;
    GPIOD->MODER |= (0x55<<24);
    GPIOD->ODR |= (0xF<<12);
    return 0;
}
