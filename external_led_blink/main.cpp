#include <stdint.h>


#define RCC_BASE      0x40021000 
#define GPIOA_BASE    0x40010800

#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18)
#define GPIOA_CRL     *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR     *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

// bit fields
#define RCC_IOPAEN   (1<<2)
#define GPIOA2       (1UL<<2)

int main()
{
    RCC_APB2ENR |= RCC_IOPAEN;
    GPIOA_CRL   &= 0xFFFFF0FF;
    GPIOA_CRL   |= 0x00000200;

    while(1)
    {
        GPIOA_ODR |=  GPIOA2;
        for (uint32_t i = 0; i < 500000; i++);
        GPIOA_ODR &= ~GPIOA2;
        for (uint32_t i = 0; i < 500000; i++); 
    }
}
