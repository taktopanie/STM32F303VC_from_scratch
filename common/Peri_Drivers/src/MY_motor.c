/*
 * ULN2003_motor.c
 *
 *  Created on: Feb 9, 2024
 *      Author: maciej
 */

#include <MY_motor.h>


///////////////////// STEPPER MOTOR WITH ULN2003 DRIVER /////////////////////

uint8_t _motor_position = 0;

void MOTOR_set_position_ULN2003 (uint8_t pos)
{

	switch (pos)
	{
		case 0:
			HAL_GPIO_WritePin(MOTOR_PORT_0_ULN2003, MOTOR_PIN_0_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_1_ULN2003, MOTOR_PIN_1_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_2_ULN2003, MOTOR_PIN_2_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_3_ULN2003, MOTOR_PIN_3_ULN2003, DISABLE);
			break;
		case 1:
		{
			HAL_GPIO_WritePin(MOTOR_PORT_0_ULN2003, MOTOR_PIN_0_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_1_ULN2003, MOTOR_PIN_1_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_2_ULN2003, MOTOR_PIN_2_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_3_ULN2003, MOTOR_PIN_3_ULN2003, DISABLE);
			break;
		}
		case 2:
		{
			HAL_GPIO_WritePin(MOTOR_PORT_0_ULN2003, MOTOR_PIN_0_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_1_ULN2003, MOTOR_PIN_1_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_2_ULN2003, MOTOR_PIN_2_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_3_ULN2003, MOTOR_PIN_3_ULN2003, ENABLE);
			break;
		}
		case 3:
		{
			HAL_GPIO_WritePin(MOTOR_PORT_0_ULN2003, MOTOR_PIN_0_ULN2003, ENABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_1_ULN2003, MOTOR_PIN_1_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_2_ULN2003, MOTOR_PIN_2_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_3_ULN2003, MOTOR_PIN_3_ULN2003, ENABLE);
			break;
		}
		case 99:
		{
			HAL_GPIO_WritePin(MOTOR_PORT_0_ULN2003, MOTOR_PIN_0_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_1_ULN2003, MOTOR_PIN_1_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_2_ULN2003, MOTOR_PIN_2_ULN2003, DISABLE);
			HAL_GPIO_WritePin(MOTOR_PORT_3_ULN2003, MOTOR_PIN_3_ULN2003, DISABLE);
			break;
		}
		default:
		{
			break;
		}

	}
}

void MOTOR_left_ULN2003 (void)
{
	MOTOR_set_position_ULN2003(_motor_position);
	if(_motor_position == 0)
	{
		_motor_position = 3;
	}else
	{
		_motor_position--;
	}
}

void MOTOR_right_ULN2003 (void)
{
	MOTOR_set_position_ULN2003(_motor_position++);
	if(_motor_position == 4)
	{
		_motor_position = 0;
	}
}


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////// SERVO CONTROL ///////////////////////////////


/*
 * Values from the datasheet:
 *
 * Period 	20 		ms
 * LEFT 	~ 2 	ms
 * CENTER 	~ 1.5 	ms
 * RIGHT 	~ 1 	ms
 * 		_____
 * 		|	|
 * 		|	|
 * 		|	|________________
 * 		<--->
 * 		  X
 * 		<------------------->
 * 		          Y
 *
 *##########################################################
 *	values retrieved after calibration with Arduino Servo.h
 *
 *	Y = 20.152 ms
 *
 *	LEFT:		X = 2.418	us
 *	CENTER:		X = 1.483	us
 *	RIGHT:		X = 5.488	us
 *##########################################################
 */

#define _servo_max		2415
#define _servo_mid		1481
#define _servo_min		548

long _map(long x, long in_min, long in_max, long out_min, long out_max);

void SERVO_set_LEFT_MAX(TIM_HandleTypeDef *htim)
{
	//TUNED WITH ARDUINO AS REFERENCE
	__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, _servo_max);
}

void SERVO_set_CENTER(TIM_HandleTypeDef *htim)
{
	//TUNED WITH ARDUINO AS REFERENCE
	__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, _servo_mid);
}

void SERVO_set_RIGHT_MAX(TIM_HandleTypeDef *htim)
{
	//TUNED WITH ARDUINO AS REFERENCE
	__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, _servo_min);
}

void SERVO_set(TIM_HandleTypeDef *htim, uint16_t angle)
{
	long value = _map(angle, 0, 180, _servo_min, _servo_max);

	__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, value);
}

void PWM_width_change(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t percent)
{
	uint32_t ARR = htim->Instance->ARR;
	uint32_t tmp = (((ARR+1) * percent / 100));
	switch(Channel)
	{
	case TIM_CHANNEL_1:
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, tmp);
		break;
	case TIM_CHANNEL_2:
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, tmp);
		break;
	case TIM_CHANNEL_3:
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, tmp);
		break;
	case TIM_CHANNEL_4:
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, tmp);
		break;
	}

}

long _map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
