/*
 * itm.c
 *
 *  Created on: July, 2024
 *      Author: Jitendra
 */
#include <stdint.h>

//Debug Exception and Monitor Control Register base address
#define DEMCR        			*((volatile uint32_t*) 0xE000EDFCU )

/* ITM register addresses */
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )

//void ITM_SendChar(uint8_t ch)
int __io_putchar(int ch)
{
	//Enable TRCENA
	DEMCR |= (1 << 24);

	//enable stimulus port 0
	ITM_TRACE_EN |= ( 1 << 0);

	// read FIFO status in bit [0]:
	while(!(ITM_STIMULUS_PORT0 & 1));

	//Write to ITM stimulus port0
	ITM_STIMULUS_PORT0 = ch;

	return 1;
}
