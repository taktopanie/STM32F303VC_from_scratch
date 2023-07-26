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
	__vo uint32_t TIMx_CR1;
	__vo uint32_t TIMx_CR2;
	__vo uint32_t TIMx_SMCR;
	__vo uint32_t TIMx_DIER;
	__vo uint32_t TIMx_SR;
	__vo uint32_t TIMx_EGR;
	__vo uint32_t TIMx_CCMR1;
	__vo uint32_t TIMx_CCMR2;
	__vo uint32_t TIMx_CCER;
	__vo uint32_t TIMx_CNT;
	__vo uint32_t TIMx_PSC;
	__vo uint32_t TIMx_ARR;
	uint32_t RESERVED_1;
	__vo uint32_t TIMx_CCR1;
	__vo uint32_t TIMx_CCR2;
	__vo uint32_t TIMx_CCR3;
	__vo uint32_t TIMx_CCR4;
	uint32_t RESERVED_2;
	__vo uint32_t TIMx_DCR;
	__vo uint32_t TIMx_DMAR;
}Timer_RegDef;

void Timer2_Init();


#endif /* INC_TIMER_LIB_H_ */
