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


void MOTOR_set_position(uint8_t pos);
void MOTOR_left (void);
void MOTOR_right (void);

#endif /* ULN2003_MOTOR_H_ */
