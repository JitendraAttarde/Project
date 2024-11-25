#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "keypad.h"

static char decode_keypad(uint8_t col, uint8_t row);



const unsigned char keymap[4][4]=
	{
		{'1', '2', '3', 'A' },
		{'4', '5', '6', 'B' },
		{'7', '8', '9', 'C' },
		{'*', '0', '#', 'D' }


	};


const uint32_t clo_state[4]={	(GPIO_BSRR_BR4|GPIO_BSRR_BS5|GPIO_BSRR_BS6|GPIO_BSRR_BS7),
						(GPIO_BSRR_BS4|GPIO_BSRR_BR5|GPIO_BSRR_BS6|GPIO_BSRR_BS7),
						(GPIO_BSRR_BS4|GPIO_BSRR_BS5|GPIO_BSRR_BR6|GPIO_BSRR_BS7),
						(GPIO_BSRR_BS4|GPIO_BSRR_BS5|GPIO_BSRR_BS6|GPIO_BSRR_BR7)
};




void keypad_init(void)
{

	/*Enable clock access to GPIOC*/
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;

	/*Set PC0 to PC3 as input*/
	GPIOC->MODER &= ~(GPIO_MODER_MODE0|GPIO_MODER_MODE1|GPIO_MODER_MODE2|GPIO_MODER_MODE3);

	/* Activate internal pullup resistor for PC0 to PC3*/
	GPIOC->PUPDR|=GPIO_PUPDR_PUPD0_0|GPIO_PUPDR_PUPD1_0|GPIO_PUPDR_PUPD2_0|GPIO_PUPDR_PUPD3_0;

	/*Set PC4 to PC7 as output*/
	GPIOC->MODER |= GPIO_MODER_MODE4_0|GPIO_MODER_MODE5_0|GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0;

	GPIOC->MODER &=~( GPIO_MODER_MODE4_1|GPIO_MODER_MODE5_1|GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1);

	/*Set PC4 to PC7 as high*/

	GPIOC->BSRR = GPIO_BSRR_BS4|GPIO_BSRR_BS5|GPIO_BSRR_BS6|GPIO_BSRR_BS7;
}


char keypad_read(void)
{

	unsigned char key=0,data=0;

	for (int i=0;i<4;i++)
	{

		GPIOC->BSRR=clo_state[i];

		data=(GPIOC->IDR)&0xF; /*Get rid of data from bit 5 to bit31*/

		if(data != 0xF)
		{
			key=decode_keypad(i,data);
		}

	}

	return key;
}


static char decode_keypad(uint8_t col, uint8_t row)
{

	if (row == 0xE) return keymap[0][col];
	if (row == 0xD) return keymap[1][col];
	if (row == 0xB) return keymap[2][col];
	if (row == 0x7) return keymap[3][col];
	return 0;
}

//
//void KeypadInit()
//{
//	RCC->AHB1ENR |= BV(KEYPD_GPIO_EN);
//
//	// Configure row pins as OUPUT
//	KEYPD_GPIO->MODER |= BV((KEYPD_R1 * 2) | (KEYPD_R2 * 2) | (KEYPD_R3 * 2) | (KEYPD_R4 * 2));
//	KEYPD_GPIO->MODER &= ~BV((KEYPD_R1 * 2 + 1) | (KEYPD_R2 * 2 + 1) | (KEYPD_R3 * 2 + 1) | (KEYPD_R4 * 2 + 1));
//
//	// Configure column pins as INPUT
//	KEYPD_GPIO->MODER &= ~BV((KEYPD_C1 * 2) | (KEYPD_C2 * 2) | (KEYPD_C3 * 2) | (KEYPD_C4 * 2));
//	KEYPD_GPIO->MODER &= ~BV((KEYPD_C1 * 2 + 1) | (KEYPD_C2 * 2 + 1) | (KEYPD_C3 * 2 + 1) | (KEYPD_C4 * 2 + 1));
//
//	// Configuring column lines with PULL-UP resistor.
//	KEYPD_GPIO->PUPDR |= BV((KEYPD_C1 * 2) | (KEYPD_C2 * 2) | (KEYPD_C3 * 2) | (KEYPD_C4 * 2));
//	KEYPD_GPIO->PUPDR &= ~BV((KEYPD_C1 * 2 + 1) | (KEYPD_C2 * 2 + 1) | (KEYPD_C3 * 2 + 1) | (KEYPD_C4 * 2 + 1));
//}
//
//char KeyPessed()
//{
//	KEYPD_GPIO->ODR |= 0X0f;
//
//	// configure R1 as low
//	KEYPD_GPIO->ODR &= ~(1 << 0);
//
//	// checking from C1 too C4
//	//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
//	if(!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
//	{
//		DelayMs(200);
//		return '1';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
//	{
//		DelayMs(200);
//		return '2';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
//	{
//		DelayMs(200);
//		return '3';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
//	{
//		DelayMs(200);
//		return 'A';
//	}
//
//	// Configuring all rows as high
//	//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
//	KEYPD_GPIO->ODR |= 0X0f;
//
//	// configure R2 as low
//	KEYPD_GPIO->ODR &= ~(1 << 1);
//	//KEYPD_GPIO->ODR &= ~BV(KEYPD_R2);
//
//	// checking from C1 too C4
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
//	{
//		DelayMs(200);
//		return '4';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
//	{
//		DelayMs(200);
//		return '5';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
//	{
//		DelayMs(200);
//		return '6';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
//	{
//		DelayMs(200);
//		return 'B';
//	}
//
//	// Configuring all rows as high
//	//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
//	KEYPD_GPIO->ODR |= 0X0f;
//
//	// configure R3 as low
//	KEYPD_GPIO->ODR &= ~(1 << 2);
//	//KEYPD_GPIO->ODR &= ~BV(KEYPD_R3);
//
//	// checking from C1 too C4
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
//	{
//		DelayMs(200);
//		return '7';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
//	{
//		DelayMs(200);
//		return '8';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
//	{
//		DelayMs(200);
//		return '9';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
//	{
//		DelayMs(200);
//		return 'C';
//	}
//
//	// Configuring all rows as high
//	//	KEYPD_GPIO->ODR |= BV((KEYPD_R1) | (KEYPD_R2) | (KEYPD_R3) | (KEYPD_R4));
//	KEYPD_GPIO->ODR |= 0X0f;
//
//	// configure R4 as low
//	KEYPD_GPIO->ODR &= ~(1 << 3);
//	//KEYPD_GPIO->ODR &= ~BV(KEYPD_R2);
//
//	// checking from C1 too C4
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C1)))
//	{
//		DelayMs(200);
//		return '*';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C2)))
//	{
//		DelayMs(200);
//		return '0';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C3)))
//	{
//		DelayMs(200);
//		return '#';
//	}
//
//	if (!(KEYPD_GPIO->IDR & BV(KEYPD_C4)))
//	{
//		DelayMs(200);
//		return 'D';
//	}
//
//	return 0;
//}

