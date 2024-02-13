/*
 * ULN2003_motor.h
 *
 *  Created on: Feb 9, 2024
 *      Author: maciej
 */

#ifndef ULN2003_MOTOR_H_
#define ULN2003_MOTOR_H_

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"
#include "stm32f3xx.h"

/*
 * MOTOR PIN DEFINITION
 */
#define MOTOR_PIN_0			GPIO_PIN_0
#define MOTOR_PORT_0		GPIOC
#define MOTOR_PIN_1			GPIO_PIN_1
#define MOTOR_PORT_1		GPIOC
#define MOTOR_PIN_2			GPIO_PIN_2
#define MOTOR_PORT_2		GPIOC
#define MOTOR_PIN_3			GPIO_PIN_3
#define MOTOR_PORT_3		GPIOC



void MOTOR_set_position(uint8_t pos);
void MOTOR_left (void);
void MOTOR_right (void);

#endif /* ULN2003_MOTOR_H_ */
