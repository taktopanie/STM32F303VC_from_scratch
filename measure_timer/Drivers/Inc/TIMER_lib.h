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

#define COUNTER_MODE_UP					0
#define COUNTER_MODE_DOWN				1

#define TIM_EDGE_RISING					0
#define TIM_EDGE_FALLING				1
#define TIM_EDGE_BOTH					2

#define TIM_INTERRUPT_1_EVENT 			0
#define TIM_INTERRUPT_2_EVENT			1
#define TIM_INTERRUPT_4_EVENT			2
#define TIM_INTERRUPT_8_EVENT			3

#define TIM_FILTERING_NO				0x0
#define TIM_FILTERING_LOW				0x3
#define TIM_FILTERING_MEDIUM			0x9
#define TIM_FILTERING_HIGH				0xF

typedef struct{
Timer_RegDef* TIMER;
uint16_t TIM_prescaler;
uint32_t TIM_ARR;
uint8_t TIM_Counter_mode;
uint8_t	TIM_OnePulse_mode;
uint8_t TIM_Edge_trigger;
uint8_t TIM_INT_PRSC;
uint8_t TIM_FILTERING;
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
 *  TODO: Rest of the settings will be added
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
 *	- TIMER_handler->TIM_Edge_trigger
 *	- TIMER_handler->TIM_INT_PRSC
 *	- TIMER_handler->TIM_FILTERING
 *
 *  // Rest of the settings will be added when will be needed (different channels... etc..)
 *
 */
void Timer_Init_INPUT_CC_MODE(Timer_Handle_t* TIMER_handler);

#endif /* INC_TIMER_LIB_H_ */
