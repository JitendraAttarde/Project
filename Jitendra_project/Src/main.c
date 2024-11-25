#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "keypad.h"
#include "servo.h"
#include "i2c_lcd.h"
#include "RFID.h"

uint8_t rfid_id[4];

int lockDoor(int locked)
{
	LedOff(LED_RED);
	while(TIM2->CCR1 < 2500)
	{
		TIM2->CCR1 = TIM2->CCR1 + 50;
		TIM4_ms_Delay(50);
	}
	LcdWrite(LCD_CMD, LCD_CLEAR);
	DelayMs(10);
	LcdPuts(LCD_LINE1, "DOOR UNLOCKED");
	LcdPuts(LCD_LINE2, "FOR 10 SECOND");
	LedOff(LED_RED);
	LedOn(LED_GREEN);
	DelayMs(7000);
	locked = 0;
	return locked;
}

int unlockDoor(int locked)
{
	LcdWrite(LCD_CMD, LCD_CLEAR);
	DelayMs(10);
	LcdPuts(LCD_LINE1, "DOOR LOCKING");
	LcdPuts(LCD_LINE2, "IN 3");
	DelayMs(1000);
	LcdPuts(LCD_LINE2, "IN 2");
	DelayMs(1000);
	LcdPuts(LCD_LINE2, "IN 1");
	DelayMs(1000);
	LcdWrite(LCD_CMD, LCD_CLEAR);
	DelayMs(10);
	while(TIM2->CCR1 > 500)
	{
		TIM2->CCR1 = TIM2->CCR1 - 50;
		TIM4_ms_Delay(50);
	}
	LedOff(LED_GREEN);
	locked = 1;
}

int main()
{
	SystemInit();
	systick_init_ms(16000000);

	// Servo-Motor Initialization
	RCC->CFGR |= 0<<10; // set APB1 = 16 MHz
	GPIO_Init();
	TIM2_Init();
	TIM2->CR1 |= 1;
	TIM2->CCR1 = 500;
	TIM4_ms_Delay(50);

	// RFID Initialization
	rc522_init();
	DelayMs(10);

	// LED Initialization
	LedInit(LED_GREEN);
	LedInit(LED_ORANGE);
	LedInit(LED_RED);
	LedInit(LED_BLUE);

	// LCD Initialization
	int ret;
	ret = LcdInit();

	// Keypad Initialization
	//	KeypadInit();
	keypad_init();
	char keyVal = 0;

	//
	int locked = 1;

	if(ret)
	{
		while(1)
		{
			if(locked == 1)
			{
				LedOn(LED_RED);
				LcdPuts(LCD_LINE1, "DOOR LOCKED");
				LcdPuts(LCD_LINE2, "RFID - PWD");
				DelayMs(100);

				keyVal=keypad_read();
				DelayMs(100);
				if(keyVal)
				{
					if(keyVal == '7')
					{
						DelayMs(100);
						locked = lockDoor(locked);
					}
					keyVal = 0;
				}

				else if(rc522_checkCard(rfid_id))
				{
					locked = lockDoor(locked);
				}
			}
			else
			{
				locked = unlockDoor(locked);
			}
		}
	}
}



