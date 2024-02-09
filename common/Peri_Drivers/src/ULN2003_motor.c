/*
 * ULN2003_motor.c
 *
 *  Created on: Feb 9, 2024
 *      Author: maciej
 */

#include "ULN2003_motor.h"

uint8_t _motor_position = 0;

void MOTOR_set_position (uint8_t pos)
{

	switch (pos)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, DISABLE);
			break;
		case 1:
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, DISABLE);
			break;
		}
		case 2:
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, ENABLE);
			break;
		}
		case 3:
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, ENABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, DISABLE);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, ENABLE);
			break;
		}
		default:
		{
			break;
		}

	}
}

void MOTOR_left (void)
{
	MOTOR_set_position(_motor_position);
	if(_motor_position == 0)
	{
		_motor_position = 3;
	}else
	{
		_motor_position--;
	}
}

void MOTOR_right (void)
{
	MOTOR_set_position(_motor_position++);
	if(_motor_position == 4)
	{
		_motor_position = 0;
	}
}
