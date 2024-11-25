#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "keypad.h"
int main(void)
{
	SystemInit();

	// Enable the GPIOD clock
	RCC->AHB1ENR |= BV(KEYPD_GPIO_EN);

	// Configure row pins as OUPUT
	KEYPD_GPIO->MODER |= BV((KEYPD_R1 * 2) | (KEYPD_R2 * 2) | (KEYPD_R3 * 2) | (KEYPD_R4 * 2));
	KEYPD_GPIO->MODER &= ~BV((KEYPD_R1 * 2 + 1) | (KEYPD_R2 * 2 + 1) | (KEYPD_R3 * 2 + 1) | (KEYPD_R4 * 2 + 1));

	// Configure column pins as INPUT
	KEYPD_GPIO->MODER &= ~BV((KEYPD_C1 * 2) | (KEYPD_C2 * 2) | (KEYPD_C3 * 2) | (KEYPD_C4 * 2));
	KEYPD_GPIO->MODER &= ~BV((KEYPD_C1 * 2 + 1) | (KEYPD_C2 * 2 + 1) | (KEYPD_C3 * 2 + 1) | (KEYPD_C4 * 2 + 1));

	// Configuring column lines with PULL-UP resistor.
	KEYPD_GPIO->PUPDR |= BV((KEYPD_C1 * 2) | (KEYPD_C2 * 2) | (KEYPD_C3 * 2) | (KEYPD_C4 * 2));
	KEYPD_GPIO->PUPDR &= ~BV((KEYPD_C1 * 2 + 1) | (KEYPD_C2 * 2 + 1) | (KEYPD_C3 * 2 + 1) | (KEYPD_C4 * 2 + 1));

	while(1)
	{
		// Configuring all rows as high
		// KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
		KEYPD_GPIO->ODR |= 0X0f;

		// configure R1 as low
		KEYPD_GPIO->ODR &= ~(1 << 0);

		// checking from C1 too C4
		//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
		if(!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
		{
			DelayMs(200);
			printf("1\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
		{
			DelayMs(200);
			printf("2\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
		{
			DelayMs(200);
			printf("3\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
		{
			DelayMs(200);
			printf("A\n");
		}

		// Configuring all rows as high
		//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
		KEYPD_GPIO->ODR |= 0X0f;

		// configure R2 as low
		KEYPD_GPIO->ODR &= ~(1 << 1);
		//KEYPD_GPIO->ODR &= ~BV(KEYPD_R2);

		// checking from C1 too C4
		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
		{
			DelayMs(200);
			printf("4\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
		{
			DelayMs(200);
			printf("5\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
		{
			DelayMs(200);
			printf("6\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
		{
			DelayMs(200);
			printf("B\n");
		}

		// Configuring all rows as high
		//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
		KEYPD_GPIO->ODR |= 0X0f;

		// configure R3 as low
		KEYPD_GPIO->ODR &= ~(1 << 2);
		//KEYPD_GPIO->ODR &= ~BV(KEYPD_R3);

		// checking from C1 too C4
		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
		{
			DelayMs(200);
			printf("7\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
		{
			DelayMs(200);
			printf("8\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
		{
			DelayMs(200);
			printf("9\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
		{
			DelayMs(200);
			printf("C\n");
		}

		// Configuring all rows as high
		//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
		KEYPD_GPIO->ODR |= 0X0f;

		// configure R4 as low
		KEYPD_GPIO->ODR &= ~(1 << 3);
		//KEYPD_GPIO->ODR &= ~BV(KEYPD_R2);

		// checking from C1 too C4
		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
		{
			DelayMs(200);
			printf("*\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
		{
			DelayMs(200);
			printf("0\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
		{
			DelayMs(200);
			printf("#\n");
		}

		if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
		{
			DelayMs(200);
			printf("D\n");
		}
	}
	return 0;
}
