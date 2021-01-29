#include <stdint.h>


#define RCC_BASE      0x40021000 // Начальный бит для работы с тактированием(стр.51)
#define GPIOC_BASE    0x40011000 // Адрес выводов GPIOC

#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18) // подача тактирования на ножку(стр 121)
#define GPIOC_CRH     *(volatile uint32_t *)(GPIOC_BASE + 0x04) // выбор ножки на которую подаются тактирование(стр.194
#define GPIOC_ODR     *(volatile uint32_t *)(GPIOC_BASE + 0x0C) // регистр управления портом (стр.194)

// bit fields
#define RCC_IOPCEN   (1<<4) // записать в 4 бит 1
#define GPIOC13      (1UL<<13)

int main()
{
    RCC_APB2ENR |= RCC_IOPCEN;
    GPIOC_CRH   &= 0xFF0FFFFF;
    GPIOC_CRH   |= 0x00200000;

    while(1)
    {
        GPIOC_ODR |=  GPIOC13;
        for (uint32_t i = 0; i < 429496; i++);
        GPIOC_ODR &= ~GPIOC13;
        for (uint32_t i = 0; i < 429496; i++); 
    }
}