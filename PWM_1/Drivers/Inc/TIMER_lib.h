/*
 * timer_lib.h
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#ifndef INC_TIMER_LIB_H_
#define INC_TIMER_LIB_H_

#include<stm32f3xx.h>

#define __vo volatile
#define COUNTER_MODE_UP			0
#define COUNTER_MODE_DOWN		1


typedef struct{
Timer_RegDef* TIMER;
uint16_t TIM_PRESCALLER;
uint32_t TIM_ARR;
uint8_t TIM_COUNTER_mode;
uint8_t	TIM_ONEPULSE;
uint8_t TIM_PWM_INVERTED_MODE;
uint8_t TIM_PWM_WIDTH_PERCENT;

}Timer_Handle_t;

/*
 * Timer free run configuration function - counts to a given time and generates interrupt
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler->TIM_ARR
 *  - TIMER_handler->TIM_prescaler
 *  - TIMER_handler->TIMER
 *  - TIMER_handler->TIM_Counter_mode
 *
 *  optional:
 *  - TIMER_handler->TIM_OnePulse_mode
 *  TODO: Rest of the settings will be added SOON
 *
 */
void Timer_Init_FREE_RUN(Timer_Handle_t* TIMER_handler);

/*
 * Timer input capture/compare configuration function
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler->TIM_ARR
 *  - TIMER_handler->TIM_prescaler
 *  - TIMER_handler->TIMER
 *	- TIMER_handler->counter mode
 *
 *  TODO: Rest of the settings will be added
 *
 *	- TIMER_handler->RISING EDGE
 *	- TIMER_handler->filter
 *	- TIMER_handler->TI1 input
 */
void Timer_Init_INPUT_CC_MODE(Timer_Handle_t* TIMER_handler);

/*
 * Timer input capture/compare configuration function
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler->TIM_ARR
 *  - TIMER_handler->TIM_prescaler
 *  - TIMER_handler->TIMER
 *	- TIMER_handler->PWM_inverted mode
 *	- Tuner_handler->PWM_width_percent (value between 0 and 100);
 *
 *  TODO: Rest of the settings will be added, Other channels will be added
 */
void Timer_Init_PWM_MODE(Timer_Handle_t* TIMER_handler);


#endif /* INC_TIMER_LIB_H_ */
