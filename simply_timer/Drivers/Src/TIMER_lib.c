/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
#include <TIMER_lib.h>


void Timer_Init(Timer_Handle_t* TIMER_handler){

	//Turn on TIM clock
	if(TIMER_handler->TIMER == TIMER2){
		RCC->APB1ENR |= (1<<0);
	}else if(TIMER_handler->TIMER == TIMER3){
		RCC->APB1ENR |= (1<<1);
	}else if(TIMER_handler->TIMER == TIMER4){
		RCC->APB1ENR |= (1<<2);
	}

	//set ARR and PRESCALER
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;
	TIMER_handler->TIMER->TIMx_PSC |= TIMER_handler->TIM_prescaler;

	//allow to generate update
	TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//turn on TIMER
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	//update shadow values
	TIMER_handler->TIMER->TIMx_EGR |= (1<<0);
}
