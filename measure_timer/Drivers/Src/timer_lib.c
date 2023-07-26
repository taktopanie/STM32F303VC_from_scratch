	/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
#include <timer_lib.h>



void Timer2_Init(){

	//Turn on TIM2 clock
	RCC->APB1ENR |= (1<<0);

	Timer_RegDef *wsk_TIM = (Timer_RegDef*)0x40000000UL;

	//counter mode up == DEFAULT

	//no prescaler == DEFAULT

	//RISING EDGE == DEFAULT

	//no filter == DEFAULT

	//TI1 input
	wsk_TIM->TIMx_CCMR1 |= (1<<0);

	//set prescaler to 1 ms precision
	wsk_TIM->TIMx_PSC = (64000);

	//ARR max value
	wsk_TIM->TIMx_ARR = 0xFFFFFFFFUL;

	//allow to generate update
	wsk_TIM->TIMx_DIER |= (1<<0);

	//enable CCR1 interupt
	wsk_TIM->TIMx_DIER |= (1<<1);

	//turn on TIM2
	wsk_TIM->TIMx_CR1 |= (1<<0);

	//update shadow values
	wsk_TIM->TIMx_EGR |= (1<<0);

	// enable C/C interrupt
	wsk_TIM->TIMx_CCER |= (1<<0);


}
