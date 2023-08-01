/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <TIMER_lib.h>


/*
 *
 */

void __Timer_Clock_update(Timer_RegDef* timer){
	//Turn on TIM clock
	if(timer == TIMER2){
		RCC->APB1ENR |= (1<<0);
	}else if(timer == TIMER3){
		RCC->APB1ENR |= (1<<1);
	}else if(timer == TIMER4){
		RCC->APB1ENR |= (1<<2);
	}
}

void __Timer_update_reg(Timer_RegDef* timer){

	//update shadow values
	timer->TIMx_EGR |= (1<<0);
	//wait while UG flag set
	while(!(timer->TIMx_SR & (1<<0)));
	//cleare the flags
	timer->TIMx_SR &= ~(0x1F<<0);

	//wait till flag set
	while(timer->TIMx_SR & (1<<0));
}

/*
*
*
*
*/
void Timer_Init_FREE_RUN(Timer_Handle_t* TIMER_handler){

	__Timer_Clock_update(TIMER_handler->TIMER);

	//set counte mode
	TIMER_handler->TIMER->TIMx_CR1 |= (TIMER_handler->TIM_Counter_mode << 4);

	//set ARR and PRESCALER
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;
	TIMER_handler->TIMER->TIMx_PSC |= TIMER_handler->TIM_prescaler;

	//update shadow values
	__Timer_update_reg(TIMER_handler->TIMER);

	if(TIMER_handler->TIM_OnePulse_mode != 0){
		TIMER_handler->TIMER->TIMx_CR1 |= (1 << 3);
	}

	//allow to generate update
	TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//turn on TIMER
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);
}

void Timer_Init_INPUT_CC_MODE(Timer_Handle_t* TIMER_handler){

	//Turn on the TIM clock
	__Timer_Clock_update(TIMER_handler->TIMER);

	//counter mode
	TIMER_handler->TIMER->TIMx_CR1 |= (TIMER_handler->TIM_Counter_mode << 4);

	//TRIGGER EDGE
	if(TIMER_handler->TIM_Edge_trigger == TIM_EDGE_RISING){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
	}else if(TIMER_handler->TIM_Edge_trigger == TIM_EDGE_FALLING){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
		TIMER_handler->TIMER->TIMx_CCER |= (1 << 1);
	}else if(TIMER_handler->TIM_Edge_trigger == TIM_EDGE_BOTH){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
		TIMER_handler->TIMER->TIMx_CCER |= (5 << 1);
	}


	//FILTERING (noise reduction)
	TIMER_handler->TIMER->TIMx_CCMR1 |= (TIMER_handler->TIM_FILTERING<<4);

	//TI2 FILTERING
	//TIMER_handler->TIMER->TIMx_CCMR1 |= (TIMER_handler->TIM_FILTERING<<12);

	//INPUT PRESCALLER - CAPTURE MADE EVERY x EVENTS
	TIMER_handler->TIMER->TIMx_CCMR1 |= (TIMER_handler->TIM_INT_PRSC<<2);

	//TI1 input
	TIMER_handler->TIMER->TIMx_CCMR1 |= (1<<0);
	// TI2 INPUT
	//TIMER_handler->TIMER->TIMx_CCMR1 |= (1<<1);

	//set prescaler
	TIMER_handler->TIMER->TIMx_PSC = TIMER_handler->TIM_prescaler;

	//ARR max value
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;

	__Timer_update_reg(TIMER_handler->TIMER);

	//allow to generate update
	//TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//enable CCR1 interupt
	TIMER_handler->TIMER->TIMx_DIER |= (1<<1);

	//turn on the TIM
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	// enable CC channel 1 capture enable
	TIMER_handler->TIMER->TIMx_CCER |= (1<<0);

}

void Timer_indicate_time(Timer_RegDef* timer){

	//CLEAN the interrupt FLAG
	timer->TIMx_SR &= ~(0x2);

	static int var_old = 0;
	volatile long int var_curr = timer->TIMx_CR1;

	var_curr = timer->TIMx_CCR1;

	if(var_curr != var_old){
		long int MS_seconds = ((var_curr-var_old)/10);

		timer_time diff_time;
		diff_time.hours = (MS_seconds/100/3600);
		diff_time.minutes = ((MS_seconds)/100/60)%60;
		diff_time.seconds = ((MS_seconds)/100)%60;
		diff_time.ms= MS_seconds%100;

		printf("Time diff: %02d:%02d:%02d:%02d\n", diff_time.hours, diff_time.minutes, diff_time.seconds, diff_time.ms);
		var_old = var_curr;
	}
}
