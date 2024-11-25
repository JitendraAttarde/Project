#include<stdint.h>
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPD_GPIO		GPIOD
#define KEYPD_GPIO_EN    3

// Keypad Dimensions
#define KEYPAD_ROWS      4
#define KEYPAD_COLS      4

// GPIO Pin Definitions
#define GPIO_Pin_0       ((uint32_t)0x01)
#define GPIO_Pin_1       ((uint32_t)0x02)
#define GPIO_Pin_2       ((uint32_t)0x04)
#define GPIO_Pin_3       ((uint32_t)0x08)
#define GPIO_Pin_4       ((uint32_t)0x10)
#define GPIO_Pin_5       ((uint32_t)0x20)
#define GPIO_Pin_6       ((uint32_t)0x40)
#define GPIO_Pin_7       ((uint32_t)0x80)


// Keypad Pin Definitions
//#define KEYPD_R1         GPIO_Pin_0
//#define KEYPD_R2         GPIO_Pin_1
//#define KEYPD_R3         GPIO_Pin_2
//#define KEYPD_R4         GPIO_Pin_3
//#define KEYPD_C1         GPIO_Pin_4
//#define KEYPD_C2         GPIO_Pin_5
//#define KEYPD_C3         GPIO_Pin_6
//#define KEYPD_C4         GPIO_Pin_7

#define KEYPD_R1		0
#define KEYPD_R2		1
#define KEYPD_R3		2
#define KEYPD_R4        3
#define KEYPD_C1        8
#define KEYPD_C2        9
#define KEYPD_C3        10
#define KEYPD_C4        11
//
//void KeypadInit();
//char KeyPessed();
void keypad_init(void);
char keypad_read(void);

#endif // KEYPAD_H_
