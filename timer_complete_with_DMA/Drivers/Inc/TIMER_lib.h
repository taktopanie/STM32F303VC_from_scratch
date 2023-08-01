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

/*
 * @COUNTER_MODE
 */
#define COUNTER_MODE_UP			0
#define COUNTER_MODE_DOWN		1

/*
 * @TIMER_EDGE
 */
#define TIM_EDGE_RISING			0
#define TIM_EDGE_FALLING		1
#define TIM_EDGE_BOTH			2

/*
 * @IRQ_PRESCALER
 */
#define TIM_INTERRUPT_1_EVENT 			0
#define TIM_INTERRUPT_2_EVENT			1
#define TIM_INTERRUPT_4_EVENT			2
#define TIM_INTERRUPT_8_EVENT			3

/*
 * @IRQ_FILTERING
 */
#define TIM_FILTERING_NO				0x0
#define TIM_FILTERING_LOW				0x3
#define TIM_FILTERING_MEDIUM			0x9
#define TIM_FILTERING_HIGH				0xF

typedef struct{
	Timer_RegDef* TIMER;
	uint16_t TIM_PRESCALLER;
	uint32_t TIM_ARR;
	uint8_t TIM_COUNTER_mode;
	uint8_t	TIM_ONEPULSE;
	uint8_t TIM_EDGE_TRIGGER;
	uint8_t TIM_INT_PRSC;
	uint8_t TIM_FILTERING;
	uint8_t TIM_PWM_INVERTED_MODE;
	uint8_t TIM_PWM_WIDTH_PERCENT;
}Timer_Handle_t;

typedef struct{
	uint16_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t ms;
}timer_time;

/*
 * Timer free run configuration function - counts to a given time and generates interrupt
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler->TIM_ARR
 *  - TIMER_handler->TIM_prescaler
 *  - TIMER_handler->TIMER
 *  - TIMER_handler->TIM_Counter_mode. SEE @COUNTER_MODE
 *  - TIMER_handler->TIM_OnePulse_mode. 1-ON, 0-OFF
 *
 *   Rest of the settings will be added when needed
 *
 */
void Timer_Init_FREE_RUN(Timer_Handle_t* TIMER_handler);

/*
 * Timer input capture/compare configuration function
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler -> TIM_ARR
 *  - TIMER_handler -> TIM_prescaler
 *  - TIMER_handler -> TIMER
 *	- TIMER_handler -> TIM_COUNTER_mode. 	SEE @COUNTER_MODE
 *	- TIMER_handler -> TIM_EDGE_TRIGGER. 	SEE @TIMER_EDGE
 *	- TIMER_handler -> TIM_INT_PRSC			SEE @IRQ_PRESCALER
 *	- TIMER_handler -> TIM_FILTERING		SEE @IRQ_FILTERING
 *	- TIMER_handler->TIM_OnePulse_mode. 	1-ON, 0-OFF
 *
 *  // Rest of the settings will be added when will be needed (different channels... etc..)
 *
 */
void Timer_Init_INPUT_CC_MODE(Timer_Handle_t* TIMER_handler);

/*
 * Timer input capture/compare configuration function
 *  @parameters which should be passed throught TIMER_handler:
 *  - TIMER_handler->TIM_ARR
 *  - TIMER_handler->TIM_prescaler
 *  - TIMER_handler->TIMER
 *	- TIMER_handler->PWM_inverted mode		1-ON, 0-OFF
 *	- Tuner_handler->PWM_width_percent 		value between 0 and 100
 *	- TIMER_handler->TIM_OnePulse_mode. 	1-ON, 0-OFF
 *
 *  TODO: Rest of the settings will be added, Other channels will be added
 */
void Timer_Init_PWM_MODE(Timer_Handle_t* TIMER_handler);

/*
 * Timer IRQ handling
 * @param TIMER_handler - pointer to active TIMER address
 *
 */
void Timer_IRQ_handling(Timer_RegDef* TIMER_handler);

/*
 * Timer printing time function
 *	to use this function set timer precision to 0.1ms
 *	8Mhz clock = prescaler = 8000,
 */
void Timer_indicate_time(Timer_RegDef* timer);

#endif /* INC_TIMER_LIB_H_ */
