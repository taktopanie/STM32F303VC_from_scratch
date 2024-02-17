/*
 * ULN2003_motor.h
 *
 *  Created on: Feb 9, 2024
 *      Author: maciej
 */

#ifndef MY_MOTOR_H_
#define MY_MOTOR_H_

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"
#include "stm32f3xx.h"

///////////////////// STEPPER MOTOR WITH ULN2003 DRIVER /////////////////////
/*
 * MOTOR PIN DEFINITION ULN2003
 */
#define MOTOR_PIN_0_ULN2003			GPIO_PIN_0
#define MOTOR_PORT_0_ULN2003		GPIOC
#define MOTOR_PIN_1_ULN2003			GPIO_PIN_1
#define MOTOR_PORT_1_ULN2003		GPIOC
#define MOTOR_PIN_2_ULN2003			GPIO_PIN_2
#define MOTOR_PORT_2_ULN2003		GPIOC
#define MOTOR_PIN_3_ULN2003			GPIO_PIN_3
#define MOTOR_PORT_3_ULN2003		GPIOC

/*
 * STEPPER MOTOR FUNCTION DEFINITIONS
 */
void MOTOR_set_position_ULN2003(uint8_t pos);
void MOTOR_left_ULN2003 (void);
void MOTOR_right_ULN2003 (void);

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////// SERVO CONTROL ///////////////////////////////

/*
 * SERVO SG90 - SHOULD BE CONNECTED TO THE TIMER WITH SETTINGS
 * Timer mode: 		TIM_OCMODE_PWM1;
 * Prescaler:		47
 * Counter:			20119
 */

/*
 * SERVO FUNCTION DEFINITIONS
 */
void SERVO_set_LEFT_MAX(TIM_HandleTypeDef *htim);
void SERVO_set_CENTER(TIM_HandleTypeDef *htim);
void SERVO_set_RIGHT_MAX(TIM_HandleTypeDef *htim);

/*
 * SERVO_set 			- set the servo position with the given angle
 *
 * @arg htim 				- pointer to the timer which is connected with servo
 * @arg angle 				- angle / in TOWER PRO SG90 the value should be between 0 - 180
 */

void SERVO_set(TIM_HandleTypeDef *htim, uint16_t angle);

/*
 * PWM_width_change 	- change the pulse width with the given percentage
 *
 * @arg htim				- pointer to the timer which is connected with servo
 * @arg channel				- TIM_CHANNEL_1: TIM Channel 1 selected
 * 							  TIM_CHANNEL_2: TIM Channel 2 selected
 * 							  TIM_CHANNEL_3: TIM Channel 3 selected
 * 							  TIM_CHANNEL_4: TIM Channel 4 selected
 * @arg percent				- value between 0 - 100
 *
 */
void PWM_width_change(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t percent);

#endif /* MY_MOTOR_H_ */
