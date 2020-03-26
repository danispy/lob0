#include "stdint.h"

#define RCC 0x40021000 //resert and clock control
#define RCC_APB2ENR_OFFSET 0x18 //need to turn on bit 14 to reset usart1's clock

#define GPIOA_BASE 0x40010800
#define GPIOC_BASE 0x40011000
#define GPIOX_CRH_OFFSET 0x04
#define GPIOX_ODR_OFFSET 0x0c //output register

#define USART1 0x40013800 //bit 5 in the status register "read data register not empty"
#define USART_DR_OFFSET 0x04 //insert data to transmit or receive data
#define USART_BRR_OFFSET 0x08 //insert frequency of the usart
#define USART_CR2_OFFSET 0x10 //insert number of stop bits
#define USART_CR1_OFFSET 0x0c //turn on bits 2,3 and 13 to enable usart,transmitter and receiver

#define AFIO_BASE 0x40010000
#define AFIO_MAPR_OFFSET 0x04

#define SET_LED 0 //turn on
#define RESET_LED 0x2000
#define RCC_VALUES 0x20000
#define APB2_VALUES 0x4015
#define CR1_VALUES 0x200C
#define CRH_A_VALUE 0x490
#define CRH_C_VALUE 0x100000
#define USARTDIV_VALUE 0x1D4C //468.75
