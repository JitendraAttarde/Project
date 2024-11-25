#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
/*
 * servo.h
 *
 *  Created on: Aug 13, 2024
 *      Author: harsh
 */

#ifndef SERVO_H_
#define SERVO_H_

#define ARM_MATH_CM4

void GPIO_Init(void);
void TIM2_Init(void);
void TIM4_ms_Delay(uint32_t delay);


#endif /* SERVO_H_ */
