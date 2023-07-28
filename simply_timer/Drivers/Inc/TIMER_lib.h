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


typedef struct{
Timer_RegDef* TIMER;
uint16_t TIM_prescaler;
uint32_t TIM_ARR;
uint8_t TIM_Counter_mode;
uint8_t	TIM_OnePulse_mode;
}Timer_Handle_t;

#define COUNTER_MODE_UP			1
#define COUNTER_MODE_DOWN		0

void Timer_Clock_update(Timer_RegDef* timer);

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
 *  TODO: Rest of the settings will be added
 *
 */
void Timer_Init(Timer_Handle_t* TIMER_handler);


#endif /* INC_TIMER_LIB_H_ */
