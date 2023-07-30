/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
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
	//clear the flags
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

	//set counter mode
	TIMER_handler->TIMER->TIMx_CR1 |= (TIMER_handler->TIM_COUNTER_mode << 4);

	//set ARR and PRESCALER
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;
	TIMER_handler->TIMER->TIMx_PSC |= TIMER_handler->TIM_PRESCALLER;

	//update shadow values
	__Timer_update_reg(TIMER_handler->TIMER);

	if(TIMER_handler->TIM_ONEPULSE != 0){
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
	TIMER_handler->TIMER->TIMx_CR1 |= (TIMER_handler->TIM_COUNTER_mode << 4);

	//no prescaler == DEFAULT

	//RISING EDGE == DEFAULT

	//no filter == DEFAULT

	//TI1 input
	TIMER_handler->TIMER->TIMx_CCMR1 |= (1<<0);

	//set prescaler to 1 ms precision
	TIMER_handler->TIMER->TIMx_PSC = TIMER_handler->TIM_PRESCALLER;

	//ARR max value
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;

	__Timer_update_reg(TIMER_handler->TIMER);

	//allow to generate update
	TIMER_handler->TIMER->TIMx_DIER |= (1<<0);

	//enable CCR1 interupt
	TIMER_handler->TIMER->TIMx_DIER |= (1<<1);

	//turn on the TIM
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	// enable C/C interrupt
	TIMER_handler->TIMER->TIMx_CCER |= (1<<0);

}

void Timer_Init_PWM_MODE(Timer_Handle_t* TIMER_handler){
	//Turn on the TIM clock
	__Timer_Clock_update(TIMER_handler->TIMER);

	//counter mode
	TIMER_handler->TIMER->TIMx_CR1 |= (TIMER_handler->TIM_COUNTER_mode << 4);

	//set prescaler to 0.1 ms precision
	TIMER_handler->TIMER->TIMx_PSC = TIMER_handler->TIM_PRESCALLER;

	//ARR value
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;

	//OC preload enable
	TIMER_handler->TIMER->TIMx_CCMR1 |= (1 << 11);


	//TODO: add diferent channels - now its only ch2
	if(TIMER_handler->TIM_PWM_INVERTED_MODE){
		TIMER_handler->TIMER->TIMx_CCMR1 &= ~( 7 << 12 );
		TIMER_handler->TIMER->TIMx_CCMR1 |= ( 6 << 12 );
	}else{
		TIMER_handler->TIMER->TIMx_CCMR1 &= ~( 7 << 12 );
		TIMER_handler->TIMER->TIMx_CCMR1 |= ( 7 << 12 );
	}

	//PWM width percent
	uint8_t tmp_percent = (TIMER_handler->TIMER->TIMx_ARR + 1)*(TIMER_handler->TIM_PWM_WIDTH_PERCENT)/100;
	TIMER_handler->TIMER->TIMx_CCR2 |= tmp_percent;

	__Timer_update_reg(TIMER_handler->TIMER);


	//turn on the TIM
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	// enable C/C output
	TIMER_handler->TIMER->TIMx_CCER |= (1<<4);
}
