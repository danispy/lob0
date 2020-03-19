#include "stdint.h"

#define RCC 0x40021000 //resert and clock control
#define RCC_APB1RSTR_OFFSET 0x10 //need to turn on bit 18 to reset usart3's clocks
#define RCC_APB1ENC_OFFSET 0x1c //need to turn on bit 18 to enable usart3's clock
#define RCC_VALUES 0x20000

#define GPIOC_BASE 0x40011000
#define GPIOX_CRH_OFFSET 0x04
#define CRH_VALUE 0x100000
#define GPIOX_BSRR_OFFSET 0x10 //set or reset the led
#define SET_LED 0x2000 //turn on
#define RESET_LED 0x20000000 //

#define USART3 0x40004800 //bit 5 in the status register "read data register not empty"
#define USART_DR_OFFSET 0x04 //insert data to transmit or receive data
#define USART_BRR_OFFSET 0x08 //insert frequency of the usart
#define BRR_VALUE 0 //TODO: ask or calculate //
#define USART_CR1_OFFSET 0x0c //turn on bits 2,3 and 13 to enable usart,transmitter and receiver
#define CR1_VALUES 0x200C

void configRegisters()
{
	uint32_t* address = (uint32_t*)(RCC+RCC_APB1RSTR_OFFSET);
	*address = RCC_VALUES;
	
	address = (uint32_t*)(RCC+RCC_APB1ENC_OFFSET);
	*address = RCC_VALUES;
		
	address = (uint32_t*)(GPIOC_BASE+GPIOX_CRH_OFFSET);
	*address = CRH_VALUE;
	
	address = (uint32_t*)(USART3+USART_BRR_OFFSET);
	*address = BRR_VALUE;
	
	address = (uint32_t*)(USART3+USART_CR1_OFFSET);
	*address = CR1_VALUES;
}

void led(int state)
{
	uint32_t* address = (uint32_t*)(GPIOC_BASE+GPIOX_BSRR_OFFSET);
	if(state == 1)
		*address = SET_LED;
	else
		*address = RESET_LED;
}

int main()
{
	configRegisters();
	return 0;
}