/*
 * timer_lib.c
 *
 *  Created on: Jul 25, 2023
 *      Author: maciej
 */

#include <stdint.h>
#include <timer_lib.h>



void Timer2_Init(){

	// APB1 presc
	//RCC->CFGR |= ((5) << 8);
	//Turn on TIM2 clock
	RCC->APB1ENR |= (1<<0);

	Timer_RegDef *wsk_TIM = (Timer_RegDef*)0x40000000UL;

	//SYSCLK = 8 000 000 / 1000 / 8000 = 1 hz
	wsk_TIM->TIMx_ARR = (1000-1);
	wsk_TIM->TIMx_PSC |= 8000;

	//allow to generate update
	wsk_TIM->TIMx_DIER |= (1<<0);

	//turn on TIM2
	wsk_TIM->TIMx_CR1 |= (1<<0);
}
