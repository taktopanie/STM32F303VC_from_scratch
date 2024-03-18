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
	//clear the flags
	timer->TIMx_SR &= ~(0x1F<<0);

	//wait till flag set
	while(timer->TIMx_SR & (1<<0));
}

/*
*
* free_run function
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

	//TRIGGER EDGE
	if(TIMER_handler->TIM_EDGE_TRIGGER == TIM_EDGE_RISING){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
	}else if(TIMER_handler->TIM_EDGE_TRIGGER == TIM_EDGE_FALLING){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
		TIMER_handler->TIMER->TIMx_CCER |= (1 << 1);
	}else if(TIMER_handler->TIM_EDGE_TRIGGER == TIM_EDGE_BOTH){
		TIMER_handler->TIMER->TIMx_CCER &= ~(5 << 1);
		TIMER_handler->TIMER->TIMx_CCER |= (5 << 1);
	}

	//FILTERING (noise reduction)
	TIMER_handler->TIMER->TIMx_CCMR1 |= (TIMER_handler->TIM_FILTERING<<4);

	//INPUT PRESCALLER - CAPTURE MADE EVERY x EVENTS
	TIMER_handler->TIMER->TIMx_CCMR1 &= ~(3<<2);
	TIMER_handler->TIMER->TIMx_CCMR1 |= (TIMER_handler->TIM_INT_PRSC<<2);

	//TI1 input selection
	TIMER_handler->TIMER->TIMx_CCMR1 |= (1<<0);

	//set prescaler
	TIMER_handler->TIMER->TIMx_PSC = TIMER_handler->TIM_PRESCALLER;

	//set TIMER ARR
	TIMER_handler->TIMER->TIMx_ARR = TIMER_handler->TIM_ARR;


	__Timer_update_reg(TIMER_handler->TIMER);

	//enable CCR1 interupt
	TIMER_handler->TIMER->TIMx_DIER |= (1<<1);

	//turn on the TIM
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	// enable CC channel 1 capture enable
	TIMER_handler->TIMER->TIMx_CCER |= (1<<0);
///////////////////////////////////////////////////////////////TESTTESTESTES
	//TEST DMA CC1
	TIMER_handler->TIMER->TIMx_DIER |= (1<<9);
	// differentiate INPUT CHANNELS == maybe in the future
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
	uint32_t tmp_percent = (TIMER_handler->TIMER->TIMx_ARR + 1)*(TIMER_handler->TIM_PWM_WIDTH_PERCENT)/100;
	TIMER_handler->TIMER->TIMx_CCR2 &= ~(0xFFFFFFFF);
	TIMER_handler->TIMER->TIMx_CCR2 |= tmp_percent;


	__Timer_update_reg(TIMER_handler->TIMER);


	//turn on the TIM
	TIMER_handler->TIMER->TIMx_CR1 |= (1<<0);

	// enable C/C output
	TIMER_handler->TIMER->TIMx_CCER |= (1<<4);
}

void Timer_IRQ_handling(Timer_RegDef* TIMER_pointer){

	//UIF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<0)){
		TIMER_pointer->TIMx_SR &= ~(1<<0);
		//body of particular irq
	}

	//OC1IF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<1)){
		TIMER_pointer->TIMx_SR &= ~(1<<1);
	}

	//OC2IF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<2)){
		TIMER_pointer->TIMx_SR &= ~(1<<2);
	}

	//OC3IF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<3)){
		TIMER_pointer->TIMx_SR &= ~(1<<3);
	}

	//OC4IF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<4)){
		TIMER_pointer->TIMx_SR &= ~(1<<4);
	}

	//TIF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<6)){
		TIMER_pointer->TIMx_SR &= ~(1<<6);
	}

	//CC1OF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<9)){
		TIMER_pointer->TIMx_SR &= ~(1<<9);
	}

	//CC2OF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<10)){
		TIMER_pointer->TIMx_SR &= ~(1<<10);
	}

	//CC3OF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<11)){
		TIMER_pointer->TIMx_SR &= ~(1<<11);
	}

	//CC4OF interrupt
	if(TIMER_pointer->TIMx_SR & (1<<12)){
		TIMER_pointer->TIMx_SR &= ~(1<<12);
	}

}

void Timer_indicate_time(Timer_RegDef* timer){

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

void TIMER_interrupt_set(Timer_RegDef* wsk_tim){
	uint32_t * wsk;
	wsk = (uint32_t*)(NVIC_VECT_0);

	//Enable NVIC interrupt
	if(wsk_tim == TIMER2){
		//28 line interrupt TIM2
		*wsk |= (1<< 28);
	}else if(wsk_tim == TIMER3){
		//29 line interrupt TIM3
		*wsk |= (1<< 29);
	}else if(wsk_tim == TIMER4){
		//30 line interrupt TIM4
		*wsk |= (1<< 30);
	}
}

void TIMER_DeInit(Timer_Handle_t* tim)
{
	tim->TIMER = 0;
	tim->TIM_ARR = 0;
	tim->TIM_COUNTER_mode = 0;
	tim->TIM_EDGE_TRIGGER = 0;
	tim->TIM_FILTERING = 0;
	tim->TIM_INT_PRSC = 0;
	tim->TIM_ONEPULSE = 0;
	tim->TIM_PRESCALLER = 0;
	tim->TIM_PWM_INVERTED_MODE = 0;
	tim->TIM_PWM_WIDTH_PERCENT = 0;



}
