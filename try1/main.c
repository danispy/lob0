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

void configRegisters()
{
	uint32_t* address = (uint32_t*)(RCC+RCC_APB2ENR_OFFSET);
	*address = APB2_VALUES;
		
	address = (uint32_t*)(GPIOC_BASE+GPIOX_CRH_OFFSET);
	*address = CRH_C_VALUE;
	
	address = (uint32_t*)(GPIOA_BASE+GPIOX_CRH_OFFSET);
	*address = CRH_A_VALUE;
	
	address = (uint32_t*)(USART1+USART_BRR_OFFSET);
	*address = USARTDIV_VALUE;
	
	address = (uint32_t*)(USART1+USART_CR2_OFFSET);
	*address = 0;
	
	address = (uint32_t*)(USART1+USART_CR1_OFFSET);
	*address = CR1_VALUES;
}


void led(char state)
{
	uint32_t* address = (uint32_t*)(GPIOC_BASE+GPIOX_ODR_OFFSET);
	if(state == '1')
		*address = SET_LED;
	else if(state == '0')
		*address = RESET_LED;
}

void getMsg(uint32_t check_sr, uint32_t* sr, uint32_t* usart_dr)
{
	if(check_sr == 0b100000)
	{//received information
		char check = *usart_dr;
		*sr = (*sr)*0b1111011111;//zerofy RXNE
		led(check);	
	}
}

int main()
{
	int send_zero = 0;
	int send_one = 0;
	uint32_t check_sr = 0;
	uint32_t* sr = (uint32_t*)(USART1);
	uint32_t* usart_dr = (uint32_t*)(USART1+USART_DR_OFFSET);
	configRegisters();
	led('0');
	while(1)
	{
		if(send_one == 1)
			*usart_dr = '1';//send '1'
		check_sr = (*sr)&(0b100000);
		getMsg(check_sr, sr, usart_dr);
		if(send_zero == 1)
			*usart_dr = '0';//send '0'
		check_sr = (*sr)&(0b100000);
		getMsg(check_sr, sr, usart_dr);
	}
	return 0;
}

