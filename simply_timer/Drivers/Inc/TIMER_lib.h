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
}Timer_Handle_t;

void Timer_Init(Timer_Handle_t* TIMER_handler);


#endif /* INC_TIMER_LIB_H_ */
